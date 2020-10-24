void setup_wifi() {
  
  delay(500);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(Ssid);
  WiFi.begin(Ssid, Password);

 
  if (not wifisetup){
  while (WiFi.status() != WL_CONNECTED and not wifisetup) {
    
     //if (digitalRead(0) == LOW) {
   timeout++; 
   if (timeout > 40){   wifisetup = true;}
  
   //Serial.println("GPIO LOW");
  //}
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print(".");
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
  
  }
  
  if (WiFi.status() == WL_CONNECTED){
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
      if (not wifisetup){
        IPAddress ip(MqttIp1, MqttIp2, MqttIp3, MqttIp4);
        client.setServer(ip, MqttPort);
        client.setCallback(callback);
      }
  }
  }
  if (wifisetup){
  Serial.println();
  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP("RTLsoftAP_01", "dracena1") ? "Ready" : "Failed!");
  Serial.println(WiFi.softAPIP());
  }
}
