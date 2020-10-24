#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
//#include <PID_v1.h>




//#################################################################################################################
//### Aux Clases                 ##################################################################################
//#################################################################################################################

class timer
{
  public: 
   int timeSP;
   int timeAct;
   bool en;
   bool q;
  

  void go() {
    now = millis();
    if (not en) {startTime = now;}
    if (startTime > now) {startTime = now;}
    timeAct = now - startTime;
    if (en and timeAct >= timeSP){q=true;}
    else {q=false;}
  
    } 

   void go(int SP){
    timeSP = SP;
    go();
   }

  private:
    int now;
    int startTime;
    int targetTime;
    
  
  void init() {
    en = false;
    q = false;
    }   
};

//#################################################################################################################

class blinking{
  public: 
   bool q;

   bool go(int onTime, int offTime){
      onTimer.timeSP = onTime;
      onTimer.go();
      onTimer.en = q;
      if (onTimer.q){
        q = false;  
      }
      
      offTimer.timeSP = offTime;
      offTimer.go();
      offTimer.en = not q;
      if (offTimer.q){
        q = true;
      }
      
       return q;    
   }

   private:
   timer onTimer;
   timer offTimer;
   
 };

//#################################################################################################################
//### PID Loop                   ##################################################################################
//#################################################################################################################
class PID_Control {

public:
double CV; //sygnał sterujący
double PV; //wartośc mierzona
double SP; //Nastawa
bool CoolingMode; // tryb regulacji odwrotnej
double ManualCV;// wartość wyjscia dla trybu manualnego




double Kp; //wzmocnienie proporcjonalne
double Ki; //stała całkowania
double Kd; //stała różniczkowania

double CVi;
double CVd;
double CVp;



private:
  double dt; //co ile pobiera się próbkę
  double ep; //uchyb poprzedni
  double en; //uchyb następny
  double C; //część całkująca
  int now;
  int last;
  timer TAKT;

public: void SetPar(double setKp, double setKi, double setKd){
  Kp = setKp;
  Ki = setKi;
  Kd = setKd;
}

public: void resetLoop(){

  ep = 0;
  en = 0;
  C = 0;
  
}

private: void go(int CycleTime)
  { //now = millis();
    //dt = (now-last)/1000;
    //last = now;
    dt = double(CycleTime)/1000;
            
    if (not CoolingMode){
    en = SP-PV;
    }
    else {
      en = PV-SP;
    }
    
 C += ((ep + en)/2)*dt; //całka
 
  if (C>100-abs(CVp)){C=100-abs(CVp);};
  if (C<-abs(CVp)){C=-abs(CVp);};


if (Ki>0){
  CVi = (1/Ki)*C;}
else {
  CVi = 0;
}

 if (Kd>0){
  CVd = Kd*(en - ep)/dt;
   }
 else{
  CVd = 0;
 }

 CVp = Kp*en;
 if (CVp>100){CVp=100;};
 if (CVp<-100){CVp=-100;};

 
 //CV = Kp*(en + CVi + CVd);
 CV = CVp + CVi + CVd;
 if (CV>100){CV=100;}
 if (CV<0){CV=0;}
 ep = en;
}

public: double autoMode(double setSP, double setPV, int CycleTime){
  SP = setSP;
  PV = setPV;
  
  TAKT.timeSP = CycleTime;
      TAKT.go();
      TAKT.en = not TAKT.q;
      
  if (TAKT.q){
    go(CycleTime);
    }    

  
  return CV;
}

  public: double manualMode(double ManualCV){
  resetLoop();  
  C =0; 
  CV = ManualCV;
  return CV;
}

};

//#################################################################################################################
//### Thermostat class           ##################################################################################
//#################################################################################################################

class thermostat

{
  public:
    double PV;
    double SP;
    String ControlMode;
    double CV; 
    bool PWMout;
    const double PWMtime = 10000; //10s

    double Kp;
    double Ki;
    double Kd;

  private:
    int CM;  
    PID_Control ControlLoop;
    blinking PWM;
  

public: void go(){
  int OnTime;
  int OffTime;

    
  ControlLoop.SetPar(Kp,Ki,Kd);
  CV = ControlLoop.autoMode(SP, PV, 250);
  OnTime = PWMtime * CV / 100;
  OffTime = PWMtime - OnTime;

  if (CV>0){
      PWMout = PWM.go(OnTime,OffTime);
     }
  else {
    PWMout = false;
  }
  

     
}  



   
public: void MQTTsetMode(String CM){
    if (CM != "heat"){
      ControlMode = "off";
      SP = 5.00;}
    else {
      ControlMode = "heat";
      if  (SP <= 5.00) {
      SP = 21.00;      
      }
    }
  }
public:   void MQTTsetSP(String TEMP){
    SP =  TEMP.toDouble();
    if (SP < 5.0){ SP = 5.0;}
    if (SP > 30.0){ SP = 30.0;}
        
  }  

public:   void MQTTsetTempPV(String TEMP){
    PV =  TEMP.toDouble();
         
  }  

public:   void init() {
    ControlMode = "heat";
    SP = 21.0;
    CV = 0.0; 
  } 
  

    


};

//#################################################################################################################
//### Tag Definitions            ##################################################################################
//#################################################################################################################

WiFiClient FTherm01;
PubSubClient client(FTherm01);
ESP8266WebServer server(80);

  const char addrSsid = 0;
  const char addrWifiPass = 30;
  const char addrMqttUser = 60;
  const char addrMqttPass = 90;
  const char addrMqrrPort = 120;
  const char addrMqttIp1 = 130;
  const char addrMqttIp2 = 131;
  const char addrMqttIp3 = 132;
  const char addrMqttIp4 = 133;
  const char addrThermostatStart = 140;





  

bool wifisetup = false;

thermostat Thermostat[6];
bool RecPump = false;

timer InfoTimer;
timer PIDsTrigger;
blinking LedBlink;

// const char* ssid = "NaszaSiecNET_4508_1p";
//const char* ssid = "NaszaSiec.NET_4508";
// const char* password = "7g6f73ie";
// const char* mqtt_server = "192.168.100.64";
// const int mqtt_port = 1883;

 String Ssid ="";
 String Password ="";
 String MqttPassword ="";
 String MqttUser ="";
 int MqttPort ;
 int MqttIp1;
 int MqttIp2;
 int MqttIp3;
 int MqttIp4;


void PrintInfo(){

 for (int Idx = 1; Idx <= 5; Idx++){
      Serial.print("Temperature controler info for zone nr ");
      Serial.println(Idx);
      
      Serial.print("Sensor temperature=");
      Serial.println(Thermostat[Idx].PV);
      Serial.print("Temperature set point=");
      Serial.println(Thermostat[Idx].SP);
      Serial.print("Control mode=");
      Serial.println(Thermostat[Idx].ControlMode);
  
      
 }
 
}

//#################################################################################################################
//#################################################################################################################
//### Main Program               ##################################################################################
//#################################################################################################################
//#################################################################################################################


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(0,INPUT);
  Serial.begin(115200);
  EEPROM.begin(512);
  delay(500);

  const int D0 = 16;
  const int D1 = 5;
  const int D2 = 4;
  const int D3 = 0;
  const int D4 = 2;
  const int D5 = 14;
  const int D6 = 12;
  const int D7 = 13;
  const int D8 = 15;

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  


  Ssid = ERD_String(addrSsid,30);
  Password = ERD_String(addrWifiPass,30);
  MqttPassword = ERD_String(addrMqttPass, 30);
  MqttUser = ERD_String(addrMqttUser, 30);
  MqttPort = ERD_String(addrMqrrPort, 10).toInt();

  MqttIp1 = EEPROM.read(addrMqttIp1);
  MqttIp2 = EEPROM.read(addrMqttIp2);
  MqttIp3 = EEPROM.read(addrMqttIp3);
  MqttIp4 = EEPROM.read(addrMqttIp4);

  Thermostat[1].Kp = ERD_Double(140);
  Thermostat[1].Ki = ERD_Double(144);
  Thermostat[1].Kd = ERD_Double(148);

  Thermostat[2].Kp = ERD_Double(140+16);
  Thermostat[2].Ki = ERD_Double(144+16);
  Thermostat[2].Kd = ERD_Double(148+16);

  Thermostat[3].Kp = ERD_Double(140+32);
  Thermostat[3].Ki = ERD_Double(144+32);
  Thermostat[3].Kd = ERD_Double(148+32);

  Thermostat[4].Kp = ERD_Double(140+48);
  Thermostat[4].Ki = ERD_Double(144+48);
  Thermostat[4].Kd = ERD_Double(148+48);

  Thermostat[5].Kp = ERD_Double(140+64);
  Thermostat[5].Ki = ERD_Double(144+64);
  Thermostat[5].Kd = ERD_Double(148+64);
  
  
  setup_wifi();
  
//HTTP Serwer
//**********************************************
    if (MDNS.begin("FTherm01")) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", handleRoot);
  
  server.on("/wifi", handleConSet);
  server.on("/mqtt", handleMqttSet);
  server.on("/zonedata",handleZoneData);
  server.onNotFound(handleNotFound);

  server.on("/GetProcessData",handleGetProcessData);

  server.on("/tSp1",handleTSP1);
    server.on("/tSp2",handleTSP2);
      server.on("/tSp3",handleTSP3);
        server.on("/tSp4",handleTSP4);
          server.on("/tSp5",handleTSP5);

         
 
  server.begin();
  Serial.println("HTTP server started");
//**********************************************

for (int Idx = 1; Idx <= 5; Idx++){
  if (Thermostat[Idx].ControlMode == ""){
Thermostat[Idx].init();
  }
}
  
}
 
//#################################################################################################################
//#################################################################################################################
void loop() {
  if (not wifisetup){
  MqttHandle();
  };
  server.handleClient();
  MDNS.update();

  InfoTimer.go(10000);
  InfoTimer.en = not InfoTimer.q;
  if (InfoTimer.q){
    SendMqttData();
    //PrintInfo();
    }

  PIDsTrigger.go(250);
  PIDsTrigger.en = not PIDsTrigger.q;
  if (PIDsTrigger.q){
   //Serial.println(Thermostat[1].PWMout); 
  }
  
RecPump = false;

for (int Idx = 1; Idx <= 5; Idx++){
   Thermostat[Idx].go();
   if (Thermostat[Idx].CV > 0){
RecPump = true;  
   } 
}

 BinOutCtrl(D1, Thermostat[1].PWMout);
 BinOutCtrl(D2, Thermostat[2].PWMout);
 BinOutCtrl(D5, Thermostat[3].PWMout);
 BinOutCtrl(D6, Thermostat[4].PWMout);
 BinOutCtrl(D7, Thermostat[5].PWMout);

 BinOutCtrl(D8, RecPump);
 

  
   
}
