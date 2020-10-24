void handleRtlSp(){
String RtlSetHTML = "";
RtlSetHTML += "<!DOCTYPE html>";
RtlSetHTML += "<html>";
RtlSetHTML += "<head>";
RtlSetHTML += "<meta charset=\"UTF-8\">";
RtlSetHTML += "<style>";

RtlSetHTML += "td, th {";
RtlSetHTML += "  border: 1px solid #dddddd;";
RtlSetHTML += "  text-align: left;";
RtlSetHTML += "  padding: 8px;";
RtlSetHTML += "}";

RtlSetHTML += "</style>";
RtlSetHTML += "</head>";
RtlSetHTML += "<body>";

RtlSetHTML += "<h2>Nastawy zaworu RTL:</h2>";
RtlSetHTML += "<form action=\"/RtlSp\" autocomplete=\"off\" method=\"POST\"  >";
RtlSetHTML += "<table>";
RtlSetHTML +=  "<tr>";
RtlSetHTML +=    "<th>Parametr</th>";
RtlSetHTML +=    "<th>Wartość</th>";
RtlSetHTML +=  "</tr>";
RtlSetHTML +=  "<tr>";
RtlSetHTML +=    "<td>Tryb pracy</td>";
RtlSetHTML +=    "<td><select name=\"CM\" id=\"CM\">";
RtlSetHTML +=          "<option value=\"off\"";
RtlSetHTML +=          ">off</option>";
if (Rtl.ControlMode=="off"){RtlSetHTML += " selected=\"selected\"";}
RtlSetHTML +=          "<option value=\"heat\"";
if (Rtl.ControlMode=="heat"){RtlSetHTML += " selected=\"selected\"";}
RtlSetHTML +=          ">grzanie</option></td>";
RtlSetHTML +=  "</tr>";
RtlSetHTML +=  "<tr>";
RtlSetHTML +=    "<td>Temperatura</td>";
RtlSetHTML +=    "<td><input type=\"number\" id=\"TSP\" name=\"TSP\" step = 0.1 value= "+String(Rtl.SP)+"></td>";
RtlSetHTML +=  "</tr>";
RtlSetHTML +=  "<tr>";
RtlSetHTML +=    "<td><b>Nastawy regulatora PID</b></td>";
RtlSetHTML +=    "<td></td>";
RtlSetHTML +=  "</tr>";
RtlSetHTML +=  "<tr>";
RtlSetHTML +=    "<td>Kp</td>";
RtlSetHTML +=    "<td><input type=\"number\" id=\"Kp\" name=\"Kp\" step = 0.01 value= "+String(Rtl.Kp)+"></td>";
RtlSetHTML +=  "</tr>";
RtlSetHTML +=  "<tr>";
RtlSetHTML +=    "<td>Ki</td>";
RtlSetHTML +=    "<td><input type=\"number\" id=\"Ki\" name=\"Ki\" step = 0.01 value= "+String(Rtl.Ki)+"></td>";
RtlSetHTML +=  "</tr>";
RtlSetHTML +=  "<tr>";
RtlSetHTML +=    "<td>Kd</td>";
RtlSetHTML +=    "<td><input type=\"number\" id=\"Kd\" name=\"Kd\" step = 0.01 value= "+String(Rtl.Kd)+"></td>";
RtlSetHTML +=  "</tr>";
RtlSetHTML += "</table>";
RtlSetHTML +=  "<input type=\"submit\" value=\"Zapisz\" >";
RtlSetHTML += "</form> ";
RtlSetHTML += "<br> ";
RtlSetHTML += "<a href=\"/\">Anuluj</A>";
RtlSetHTML += "</body>";
RtlSetHTML += "</html>";

if (server.hasArg("TSP") && server.hasArg("CM") && server.hasArg("Kp")&& server.hasArg("Ki")&& server.hasArg("Kd")) {
    SubmitRtlPar();
  }
  else {
    server.send(200, "text/html", RtlSetHTML);
  }

}

//########################################################################################################################
//########################################################################################################################

void SubmitRtlPar(){
  String response = "<p>Dane zapisane</p><br>";
 
 double Kp = server.arg("Kp").toDouble();
 double Ki = server.arg("Ki").toDouble();
 double Kd = server.arg("Kd").toDouble(); 
 double TSP = server.arg("TSP").toDouble(); 
 
 delay(100);

 
 Rtl.ControlMode = server.arg("CM");



if ( Rtl.Kp != Kp || Rtl.Ki != Ki || Rtl.Kd != Kd || Rtl.SP != TSP ){
 Rtl.Kp = Kp;
 Rtl.Ki = Ki;
 Rtl.Kd = Kd;
 Rtl.SP = TSP;
  
 EWR_Double(addrRTLStart, Rtl.Kp);
 EWR_Double(addrRTLStart+4, Rtl.Ki);
 EWR_Double(addrRTLStart+8, Rtl.Kd);
 EWR_Double(addrMaxRetTemp, Rtl.SP);
 
  response +="<p>Nastawy regulatora PID zapisane do EEPROM </p>"; 
}


 response +="<a href=\"/\">Menu</A>";
 server.send(200, "text/html", response); 
  
  
  
  
  
  }
