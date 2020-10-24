void handleThSp(){
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

ThSetHTML += "<h2>Nastawy termostatu:</h2>";
ThSetHTML += "<form action=\"/ThSp\" autocomplete=\"off\" method=\"POST\"  >";
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
if (Thermostat.ControlMode=="off"){ThSetHTML += " selected=\"selected\"";}
ThSetHTML +=          "<option value=\"heat\"";
if (Thermostat.ControlMode=="heat"){ThSetHTML += " selected=\"selected\"";}
ThSetHTML +=          ">grzanie</option></td>";
ThSetHTML +=  "</tr>";
ThSetHTML +=  "<tr>";
ThSetHTML +=    "<td>Temperatura</td>";
ThSetHTML +=    "<td><input type=\"number\" id=\"TSP\" name=\"TSP\" step = 0.1 value= "+String(Thermostat.SP)+"></td>";
ThSetHTML +=  "</tr>";
ThSetHTML +=  "<tr>";
ThSetHTML +=    "<td><b>Nastawy regulatora PID</b></td>";
ThSetHTML +=    "<td></td>";
ThSetHTML +=  "</tr>";
ThSetHTML +=  "<tr>";
ThSetHTML +=    "<td>Kp</td>";
ThSetHTML +=    "<td><input type=\"number\" id=\"Kp\" name=\"Kp\" step = 0.01 value= "+String(Thermostat.Kp)+"></td>";
ThSetHTML +=  "</tr>";
ThSetHTML +=  "<tr>";
ThSetHTML +=    "<td>Ki</td>";
ThSetHTML +=    "<td><input type=\"number\" id=\"Ki\" name=\"Ki\" step = 0.01 value= "+String(Thermostat.Ki)+"></td>";
ThSetHTML +=  "</tr>";
ThSetHTML +=  "<tr>";
ThSetHTML +=    "<td>Kd</td>";
ThSetHTML +=    "<td><input type=\"number\" id=\"Kd\" name=\"Kd\" step = 0.01 value= "+String(Thermostat.Kd)+"></td>";
ThSetHTML +=  "</tr>";
ThSetHTML += "</table>";
ThSetHTML +=  "<input type=\"submit\" value=\"Zapisz\" >";
ThSetHTML += "</form> ";
ThSetHTML += "<br> ";
ThSetHTML += "<a href=\"/\">Anuluj</A>";
ThSetHTML += "</body>";
ThSetHTML += "</html>";

if (server.hasArg("TSP") && server.hasArg("CM") && server.hasArg("Kp")&& server.hasArg("Ki")&& server.hasArg("Kd")) {
    SubmitPar();
  }
  else {
    server.send(200, "text/html", ThSetHTML);
  }

}

//########################################################################################################################
//########################################################################################################################

void SubmitPar(){
  String response = "<p>Dane zapisane</p><br>";
 
 double Kp = server.arg("Kp").toDouble();
 double Ki = server.arg("Ki").toDouble();
 double Kd = server.arg("Kd").toDouble(); 

 
 delay(100);

 Thermostat.SP = server.arg("TSP").toDouble();
 Thermostat.ControlMode = server.arg("CM");



if ( Thermostat.Kp != Kp || Thermostat.Ki != Ki || Thermostat.Kd != Kd){
 Thermostat.Kp = Kp;
 Thermostat.Ki = Ki;
 Thermostat.Kd = Kd;
  
 EWR_Double(addrThermostatStart, Thermostat.Kp);
 EWR_Double(addrThermostatStart+4, Thermostat.Ki);
 EWR_Double(addrThermostatStart+8, Thermostat.Kd);
 
  response +="<p>Nastawy regulatora PID zapisane do EEPROM </p>"; 
}


 response +="<a href=\"/\">Menu</A>";
 server.send(200, "text/html", response); 
  
  
  
  
  
  }
