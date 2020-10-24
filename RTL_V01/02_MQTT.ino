//------------------------------------------------------------------------------------------
void MqttHandle(){
 if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("FTherm01"); 
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    //Serial.println(MqttPrepStr(MqttUser));
    //Serial.println(MqttPrepStr(MqttPassword));

    char User[MqttUser.length()+1];
    char Pass[MqttPassword.length()+1];
    MqttUser.toCharArray(User,MqttUser.length()+1); 
    MqttPassword.toCharArray(Pass,MqttPassword.length()+1); 
    
    
    if (client.connect("RTLv01",User,Pass)) {
      Serial.println("connected");  

    // Topics:
       
      client.subscribe("RTLv01/Input/PV");
      client.subscribe("RTLv01/Input/SP");
      client.subscribe("RTLv01/Input/ControlMode");
      
      
    } else {
        timeoutMQTT++;
        if (timeoutMQTT <5){
          Serial.print("failed, rc=");
          Serial.print(client.state());
          Serial.println(" try again in 5 seconds");
          // Wait 5 seconds before retrying
          delay(5000);
        }
        else {
          mqttFail = true;
          Serial.println("failed - please check configuration");
          break;
        }
    }
  }
}

//------------------------------------------------------------------------------------------
void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // External temperature sensors signal from master control system
  
  if(topic=="RTLv01/Input/PV"){
   Thermostat.MQTTsetTempPV(messageTemp);
    }

 
// Temperature set points from master control system
  
  if(topic=="RTLv01/Input/SP"){
   Thermostat.MQTTsetSP(messageTemp);
    }

  
   
// Control mode select from master system
  
  if(topic=="RTLv01/Input/ControlMode"){
   Thermostat.MQTTsetMode(messageTemp);
    }

 
}

//------------------------------------------------------------------------------------------

void SendMqttData(){
   char msg[50]; 
   String msgStr;
   MqttPublishValue("RTLv01/Output/SP",Thermostat.SP);
   MqttPublishValue("RTLv01/Output/PV",Thermostat.PV);
   MqttPublishValue("RTLv01/Output/CV",Thermostat.CV);
   MqttPublishString("RTLv01/Output/ControlMode", Thermostat.ControlMode);

   MqttPublishValue("RTLv01/Output/ControlOutput",ControlOutput);
   MqttPublishValue("RTLv01/Output/WaterTemp",Rtl.PV);
};


//------------------------------------------------------------------------------------------
char* MqttPrepVal(double Value){
  String msgStr;
  char msg[50];

   msgStr =  String(Value);
   msgStr.toCharArray(msg,msgStr.length()+1); 
   return msg;  
}

char* MqttPrepStr(String msgStr){
   char msg[50];
   msgStr.toCharArray(msg,msgStr.length()+1); 
   return msg;  
}

void MqttPublishValue(String Topic, double Value){
  String msgStr;
  char msg[50];
  char topic[50];

  Topic.toCharArray(topic,Topic.length()+1); 
  msgStr = String(Value);
  msgStr.toCharArray(msg,msgStr.length()+1);  

 client.publish(topic,msg);
   
}

void MqttPublishString(String Topic, String msgStr){
  char msg[50];
  char topic[50];

  Topic.toCharArray(topic,Topic.length()+1); 
  msgStr.toCharArray(msg,msgStr.length()+1);  

 client.publish(topic,msg);
   
}


//------------------------------------------------------------------------------------------
