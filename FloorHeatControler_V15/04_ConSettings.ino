//#################################################################################################################
//### WiFi Configuration         ##################################################################################
//#################################################################################################################

void handleConSet() {
  String  HtmlPage =  "<html>";
          HtmlPage  +="<head> <meta charset=\"UTF-8\"></head>";
          HtmlPage  += "<p></p>";
          HtmlPage  += "<header>";
          HtmlPage  += "<h1>Ustawienia systemowe</h1>";
          HtmlPage  += "</header>";
          HtmlPage  += "<form accept-charset=\"UTF-8\" action=\"/wifi\" autocomplete=\"off\" method=\"POST\" target=\"_blank\">";
          HtmlPage  += "<strong> Ustawienia sieci WiFi:</strong><hr />";
          HtmlPage  += "<label for=\"ssid\">WiFi SSID </label>";
          HtmlPage  += "<br /> <input name=\"ssid\" type=\"text\" maxlength=\"30\" size=\"30\" value=\""; 
          HtmlPage  += Ssid;//ssid;
          HtmlPage  += "\" /> <br />";
          HtmlPage  += "<label for=\"WiFiPass\">Hasło</label><br />" ;
          HtmlPage  += "<input name=\"WiFiPass\" type=\"password\" maxlength=\"30\" size=\"30\" value=\""; 
          HtmlPage  += Password;//password;
          HtmlPage  += "\" /> <br /> <br />" ;
          HtmlPage  += "<button type=\"submit\" value=\"Submit\">Zapisz</button></form>";
          HtmlPage += "<a href=\"/\">Menu</A>";
          HtmlPage  += "</html>";

  if (server.hasArg("ssid")&& server.hasArg("WiFiPass")) {
    handleSubmitConSet();
  }
  else {//Redisplay the form
    server.send(200, "text/html", HtmlPage);
  }
 
}

void handleSubmitConSet(){//dispaly values and write to memmory
  String response = "<p>Dane zapisane</p><br>";
 response +="<p>The ssid is ";
 response += server.arg("ssid");
 response +="<br>";
 response +="And the password is ";
 response +=server.arg("WiFiPass");
 response +="<br>";
 response +="</P><BR>";
 response +="<a href=\"/\">Menu</A>";
 Serial.println("handleSubmit()");
 server.send(200, "text/html", response);
 
 EWR_String(addrSsid,server.arg("ssid"));
 EWR_String(addrWifiPass,server.arg("WiFiPass"));
 
}


//#################################################################################################################
//### Mqtt Configuration         ##################################################################################
//#################################################################################################################

void handleMqttSet() {
  
  String  HtmlPage =  "<html>";
          HtmlPage += "<head> <meta charset=\"UTF-8\"></head>";
          HtmlPage += "<p></p>";
          HtmlPage += "<header>";
          HtmlPage += "<h1>Ustawienia systemowe</h1>";
          HtmlPage += "</header>";
          HtmlPage += "<form accept-charset=\"UTF-8\" action=\"/mqtt\" autocomplete=\"off\" method=\"POST\" target=\"_blank\">";
          HtmlPage += "<strong> Ustawienia MQTT:</strong><hr />";
          
          HtmlPage += "<label for=\"MqttIp1\">Adres ip serwera</label>";
          HtmlPage += "<br /> <input name=\"mqttip1\" type=\"number\" min=\"0\" max=\"255\" size=\"3\" value=\"";
          HtmlPage += String(MqttIp1);
          HtmlPage += "\"/> ";

          HtmlPage += "<input name=\"mqttip2\" type=\"number\" min=\"0\" max=\"255\" size=\"3\" value=\"";
          HtmlPage += String(MqttIp2);
          HtmlPage += "\"/> ";

          HtmlPage += "<input name=\"mqttip3\" type=\"number\" min=\"0\" max=\"255\" size=\"3\" value=\"";
          HtmlPage += String(MqttIp3);
          HtmlPage += "\"/>";

            HtmlPage += "<input name=\"mqttip4\" type=\"number\" min=\"0\" max=\"255\" size=\"3\" value=\"";
          HtmlPage += String(MqttIp4);
          HtmlPage += "\"/> <br />";
          
          HtmlPage += "<label for=\"MqttUser\">Użytkownik</label>";
          HtmlPage += "<br /> <input name=\"MqttUser\" type=\"text\" maxlength=\"30\" size=\"30\" value=\"";
          HtmlPage += MqttUser;
          HtmlPage += "\"/> <br />";
          
          HtmlPage += "<label for=\"MqttPass\">Hasło</label>";
          HtmlPage += "<br /> <input name=\"MqttPass\" type=\"password\" maxlength=\"30\" size=\"30\" value=\"";
          HtmlPage += MqttPassword;
          HtmlPage += "\"/> <br />";
          HtmlPage += "<label for=\"MqttPort\">Port</label><br />"; 
          HtmlPage += "<input name=\"MqttPort\" type=\"number\" min=\"1\" max=\"65535\" size=\"5\" value=\"";
          HtmlPage += String(MqttPort);
          HtmlPage += "\"/> <br /><br />"; 
          HtmlPage += "<button type=\"submit\" value=\"Submit\">Zapisz</button></form>";
          HtmlPage += "<a href=\"/\">Menu</A>";
          HtmlPage += "</html>"; 

if (server.hasArg("mqttip1")&& server.hasArg("mqttip2")&& server.hasArg("mqttip3")&& server.hasArg("mqttip4")&& server.hasArg("MqttPort")&& server.hasArg("MqttPass")&& server.hasArg("MqttUser")) {
    handleSubmitMqttSet();
  }
  else {
    server.send(200, "text/html", HtmlPage);
  }
     
}


void handleSubmitMqttSet(){
  String response = "<p>Dane zapisane</p><br>"; 
          response +="<p>The Mqtt serwer is ";
          response += server.arg("mqttip1");
          response += ".";
          response += server.arg("mqttip2");
          response += ".";
          response += server.arg("mqttip3");
          response += ".";
          response += server.arg("mqttip4");
          response += ".";
          response +="<br>";
          response +="And the Mqtt server port is ";
          response +=server.arg("MqttPort");
          response +="<br>";
          response +="<p>The Mqtt user is ";
          response += server.arg("MqttUser");
          response +="<br>";
          response +="And the Mqtt password is ";
          response +=server.arg("MqttPass");
          response +="<br>";
          response +="</P><BR>";
          response +="<a href=\"/\">Menu</A>";
          
 Serial.println("handleSubmit()");
 server.send(200, "text/html", response);
 
 //EWR_String(60,server.arg("MqttServer"));//30 bytes
 EEPROM.write(addrMqttIp1,server.arg("mqttip1").toInt());
 EEPROM.write(addrMqttIp2,server.arg("mqttip2").toInt());
 EEPROM.write(addrMqttIp3,server.arg("mqttip3").toInt());
 EEPROM.write(addrMqttIp4,server.arg("mqttip4").toInt());
 EEPROM.commit();
 
 EWR_String(addrMqttPass,server.arg("MqttPass"));//30 bytes
 EWR_String(addrMqttUser,server.arg("MqttUser"));//30 bytes
 EWR_String(addrMqrrPort,(server.arg("MqttPort")));//6 bytes
 EEPROM.commit();

}
