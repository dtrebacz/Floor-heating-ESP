void handleTSP1(){
  
  if (server.hasArg("TSP") && server.hasArg("CM") && server.hasArg("Kp")&& server.hasArg("Ki")&& server.hasArg("Kd")) {
    SubmitPar(1);
  }
  else {
    String htmlPage = handleThSetHtml(1);
    server.send(200, "text/html", htmlPage);
  }
}
void handleTSP2(){
  
  if (server.hasArg("TSP") && server.hasArg("CM") && server.hasArg("Kp")&& server.hasArg("Ki")&& server.hasArg("Kd")) {
    SubmitPar(2);
  }
  else {
    String htmlPage = handleThSetHtml(2);
    server.send(200, "text/html", htmlPage);
  }
}
void handleTSP3(){
  
  if (server.hasArg("TSP") && server.hasArg("CM") && server.hasArg("Kp")&& server.hasArg("Ki")&& server.hasArg("Kd")) {
    SubmitPar(3);
  }
  else {
    String htmlPage = handleThSetHtml(3);
    server.send(200, "text/html", htmlPage);
    
  }
}
void handleTSP4(){
  
  if (server.hasArg("TSP") &&  server.hasArg("CM") && server.hasArg("Kp")&& server.hasArg("Ki")&& server.hasArg("Kd")) {
    SubmitPar(4);
  }
  else {
    String htmlPage = handleThSetHtml(4);
    server.send(200, "text/html", htmlPage);
  }
}
void handleTSP5(){
 
  if (server.hasArg("TSP") && server.hasArg("CM") && server.hasArg("Kp") && server.hasArg("Ki")&& server.hasArg("Kd")) {
    SubmitPar(5);
  }
  else {
    String htmlPage = handleThSetHtml(5);
    server.send(200, "text/html", htmlPage);
  }
}




String  handleThSetHtml(int nr){
String ThSetHTML = "";
ThSetHTML += "<!DOCTYPE html>";
ThSetHTML += "<html>";
ThSetHTML += "<head>";
ThSetHTML += "<meta charset=\"UTF-8\">";
ThSetHTML += "<style>";

ThSetHTML += "td, th {";
ThSetHTML += "  border: 1px solid #dddddd;";
ThSetHTML += "  text-align: left;";
ThSetHTML += "  padding: 8px;";
ThSetHTML += "}";

ThSetHTML += "</style>";
ThSetHTML += "</head>";
ThSetHTML += "<body>";

ThSetHTML += "<h2>Nastawy dla strefy ";
ThSetHTML += String(nr);
ThSetHTML += "</h2>";
ThSetHTML += "<form action=\"/tSp"+String(nr)+"\" autocomplete=\"off\" method=\"POST\"  >";
ThSetHTML += "<table>";
ThSetHTML +=  "<tr>";
ThSetHTML +=    "<th>Parametr</th>";
ThSetHTML +=    "<th>Wartość</th>";
ThSetHTML +=  "</tr>";
ThSetHTML +=  "<tr>";
ThSetHTML +=    "<td>Tryb pracy</td>";
ThSetHTML +=    "<td><select name=\"CM\" id=\"CM\">";
ThSetHTML +=          "<option value=\"off\"";
ThSetHTML +=          ">off</option>";
if (Thermostat[nr].ControlMode=="off"){ThSetHTML += " selected=\"selected\"";}
ThSetHTML +=          "<option value=\"heat\"";
if (Thermostat[nr].ControlMode=="heat"){ThSetHTML += " selected=\"selected\"";}
ThSetHTML +=          ">grzanie</option></td>";
ThSetHTML +=  "</tr>";
ThSetHTML +=  "<tr>";
ThSetHTML +=    "<td>Temperatura</td>";
ThSetHTML +=    "<td><input type=\"number\" id=\"TSP\" name=\"TSP\" step = 0.1 value= "+String(Thermostat[nr].SP)+"></td>";
ThSetHTML +=  "</tr>";
ThSetHTML +=  "<tr>";
ThSetHTML +=    "<td><b>Nastawy regulatora PID</b></td>";
ThSetHTML +=    "<td></td>";
ThSetHTML +=  "</tr>";
ThSetHTML +=  "<tr>";
ThSetHTML +=    "<td>Kp</td>";
ThSetHTML +=    "<td><input type=\"number\" id=\"Kp\" name=\"Kp\" step = 0.01 value= "+String(Thermostat[nr].Kp)+"></td>";
ThSetHTML +=  "</tr>";
ThSetHTML +=  "<tr>";
ThSetHTML +=    "<td>Ki</td>";
ThSetHTML +=    "<td><input type=\"number\" id=\"Ki\" name=\"Ki\" step = 0.01 value= "+String(Thermostat[nr].Ki)+"></td>";
ThSetHTML +=  "</tr>";
ThSetHTML +=  "<tr>";
ThSetHTML +=    "<td>Kd</td>";
ThSetHTML +=    "<td><input type=\"number\" id=\"Kd\" name=\"Kd\" step = 0.01 value= "+String(Thermostat[nr].Kd)+"></td>";
ThSetHTML +=  "</tr>";
ThSetHTML += "</table>";
ThSetHTML +=  "<input type=\"submit\" value=\"Zapisz\" >";
ThSetHTML += "</form> ";
ThSetHTML += "<br> ";
ThSetHTML += "<a href=\"/\">Anuluj</A>";
ThSetHTML += "</body>";
ThSetHTML += "</html>";
delay(250);
return ThSetHTML;
  
}

void SubmitPar(int nr){
  String response = "<p>Dane zapisane</p><br>";
 //response +="<p>The temperature setpoint for thermostat "+String(nr)+ "is ";
 //response += server.arg("TSP");
 //response +="<br>";
 //response +="And the control mode is ";
 //response +=server.arg("CM");
 //response +="<br>";
 //response +="And the P is ";
 //response +=server.arg("Kp");
 //response +="<br>";
 //response +="And the Ti is ";
 //response +=server.arg("Ki");
 //response +="<br>";
 //response +="And the Td is ";
 //response +=server.arg("Kd");
 //response +="<br>";
 //response +="</P><BR>";

 double Kp = server.arg("Kp").toDouble();
 double Ki = server.arg("Ki").toDouble();
 double Kd = server.arg("Kd").toDouble(); 

 
 delay(100);

 Thermostat[nr].SP = server.arg("TSP").toDouble();
 Thermostat[nr].ControlMode = server.arg("CM");



if ( Thermostat[nr].Kp != Kp || Thermostat[nr].Ki != Ki || Thermostat[nr].Kd != Kd){
 Thermostat[nr].Kp = Kp;
 Thermostat[nr].Ki = Ki;
 Thermostat[nr].Kd = Kd;
  
 EWR_Double(140 + ((nr-1)*16), Thermostat[nr].Kp);
 EWR_Double(144 + ((nr-1)*16), Thermostat[nr].Ki);
 EWR_Double(148 + ((nr-1)*16), Thermostat[nr].Kd);
 
  response +="<p>Nastawy regulatora PID zapisane do EEPROM </p>"; 
}


 response +="<a href=\"/\">Menu</A>";
 server.send(200, "text/html", response);
}
