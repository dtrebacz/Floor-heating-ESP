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
    
    
    if (client.connect("FTherm01",User,Pass)) {
      Serial.println("connected");  

    // Topics:
       
      client.subscribe("FTherm01/Zone1/Input/PV");
      client.subscribe("FTherm01/Zone2/Input/PV");
      client.subscribe("FTherm01/Zone3/Input/PV");
      client.subscribe("FTherm01/Zone4/Input/PV");
      client.subscribe("FTherm01/Zone5/Input/PV");

      client.subscribe("FTherm01/Zone1/Input/SP");
      client.subscribe("FTherm01/Zone2/Input/SP");
      client.subscribe("FTherm01/Zone3/Input/SP");
      client.subscribe("FTherm01/Zone4/Input/SP");
      client.subscribe("FTherm01/Zone5/Input/SP");

      client.subscribe("FTherm01/Zone1/Input/ControlMode");
      client.subscribe("FTherm01/Zone2/Input/ControlMode");
      client.subscribe("FTherm01/Zone3/Input/ControlMode");
      client.subscribe("FTherm01/Zone4/Input/ControlMode");
      client.subscribe("FTherm01/Zone5/Input/ControlMode");



      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
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
  
  if(topic=="FTherm01/Zone1/Input/PV"){
   Thermostat[1].MQTTsetTempPV(messageTemp);
    }

  if(topic=="FTherm01/Zone2/Input/PV"){
   Thermostat[2].MQTTsetTempPV(messageTemp);
    }

  if(topic=="FTherm01/Zone3/Input/PV"){
   Thermostat[3].MQTTsetTempPV(messageTemp);
    }

  if(topic=="FTherm01/Zone4/Input/PV"){
   Thermostat[4].MQTTsetTempPV(messageTemp);
    } 

  if(topic=="FTherm01/Zone5/Input/PV"){
   Thermostat[5].MQTTsetTempPV(messageTemp);
    }

// Temperature set points from master control system
  
  if(topic=="FTherm01/Zone1/Input/SP"){
   Thermostat[1].MQTTsetSP(messageTemp);
    }

  if(topic=="FTherm01/Zone2/Input/SP"){
   Thermostat[2].MQTTsetSP(messageTemp);
    }

  if(topic=="FTherm01/Zone3/Input/SP"){
   Thermostat[3].MQTTsetSP(messageTemp);
    }

  if(topic=="FTherm01/Zone4/Input/SP"){
   Thermostat[4].MQTTsetSP(messageTemp);
    } 

  if(topic=="FTherm01/Zone5/Input/SP"){
   Thermostat[5].MQTTsetSP(messageTemp);
    }
   
// Control mode select from master system
  
  if(topic=="FTherm01/Zone1/Input/ControlMode"){
   Thermostat[1].MQTTsetMode(messageTemp);
    }

  if(topic=="FTherm01/Zone2/Input/ControlMode"){
   Thermostat[2].MQTTsetMode(messageTemp);
    }

  if(topic=="FTherm01/Zone3/Input/ControlMode"){
   Thermostat[3].MQTTsetMode(messageTemp);
    }

  if(topic=="FTherm01/Zone4/Input/ControlMode"){
   Thermostat[4].MQTTsetMode(messageTemp);
    } 

  if(topic=="FTherm01/Zone5/Input/ControlMode"){
   Thermostat[5].MQTTsetMode(messageTemp);
    }
}

//------------------------------------------------------------------------------------------

void SendMqttData(){
   char msg[50]; 
   String msgStr;
   MqttPublishValue("FTherm01/Zone1/Output/SP",Thermostat[1].SP);
   MqttPublishValue("FTherm01/Zone2/Output/SP",Thermostat[2].SP);
   MqttPublishValue("FTherm01/Zone3/Output/SP",Thermostat[3].SP);
   MqttPublishValue("FTherm01/Zone4/Output/SP",Thermostat[4].SP);
   MqttPublishValue("FTherm01/Zone5/Output/SP",Thermostat[5].SP);

   MqttPublishValue("FTherm01/Zone1/Output/PV",Thermostat[1].PV);
   MqttPublishValue("FTherm01/Zone2/Output/PV",Thermostat[2].PV);
   MqttPublishValue("FTherm01/Zone3/Output/PV",Thermostat[3].PV);
   MqttPublishValue("FTherm01/Zone4/Output/PV",Thermostat[4].PV);
   MqttPublishValue("FTherm01/Zone5/Output/PV",Thermostat[5].PV); 

   MqttPublishValue("FTherm01/Zone1/Output/CV",Thermostat[1].CV);
   MqttPublishValue("FTherm01/Zone2/Output/CV",Thermostat[2].CV);
   MqttPublishValue("FTherm01/Zone3/Output/CV",Thermostat[3].CV);
   MqttPublishValue("FTherm01/Zone4/Output/CV",Thermostat[4].CV);
   MqttPublishValue("FTherm01/Zone5/Output/CV",Thermostat[5].CV);

  MqttPublishString("FTherm01/Zone1/Output/ControlMode", Thermostat[1].ControlMode);
  MqttPublishString("FTherm01/Zone2/Output/ControlMode", Thermostat[2].ControlMode);
  MqttPublishString("FTherm01/Zone3/Output/ControlMode", Thermostat[3].ControlMode);
  MqttPublishString("FTherm01/Zone4/Output/ControlMode", Thermostat[4].ControlMode); 
  MqttPublishString("FTherm01/Zone5/Output/ControlMode", Thermostat[5].ControlMode);

  
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
