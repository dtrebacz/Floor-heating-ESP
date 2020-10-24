//#################################################################################################################
//### HTML Page            ########################################################################################
//#################################################################################################################
//void  handleZoneData(){
const char ThermostatDataHTML[]=
"<!DOCTYPE html>"
"<html>"
"<head>"
"<meta charset=\"UTF-8\">"
"<style>"
"td, th {"
 "border: 1px solid #dddddd;"
"}"
"</style>"
"</head>"
"<body>"

"<h2>Dane z regulatorów</h2>"

"<table>"
  "<tr>"
    "<th>Nazwa</th>"
    "<th>SP [°C]</th>"
    "<th>PV [°C]</th>"
    "<th>CV [%]</th>"
    "<th>Tryb pracy</th>"
    "<th> </th>"
  "</tr>"
  "<tr>"
    "<td>Termostat</td>"
    "<td><span id=\"SP1\">x</span></td>"
    "<td><span id=\"PV1\">x</span></td>"
    "<td><span id=\"CV1\">x</span></td>"
    "<td><span id=\"CM1\">x</span></td>"
    "<td><form method=\"get\" action=\"/ThSp\"><button type=\"submit\">Nastawy</button></form></td>"
  "</tr>"
  "<tr>"
    "<td>Regulator RTL</td>"
    "<td><span id=\"SP2\">x</span></td>"
    "<td><span id=\"PV2\">x</span></td>"
    "<td><span id=\"CV2\">x</span></td>"
    "<td><span id=\"CM2\">x</span></td>"
    "<td><form method=\"get\" action=\"/RtlSp\"><button type=\"submit\">Nastawy</button></form></td>"
  "</tr>"
    "<tr>"
    "<td>Wysterowanie zaworu</td>"
    "<td><span id=\"ControlOutput\">x</span></td>"
    "<td></td>"
    "<td></td>"
    "<td></td>"
    "<td></td>"
  "</tr>"
  
  
"</table>"
"<br><a href=\"/\">Menu</A>"
    "<script>"
       
    "setInterval(function(){getData();}, 2000);"
    "document.onshow = function(){getData()};"
          
          "function getData() {"
            "var xhttp = new XMLHttpRequest();"
          "xhttp.onreadystatechange = function() {"
          "if (this.readyState == 4 && this.status == 200) {"
          "var text = this.responseText;"
          "var array = text.split(\";\");"
          
          "document.getElementById(\"SP1\").innerHTML =array[0];"
          "document.getElementById(\"PV1\").innerHTML =array[1];"
          "document.getElementById(\"CV1\").innerHTML =array[2];"
          "document.getElementById(\"CM1\").innerHTML =array[3];"

          "document.getElementById(\"SP2\").innerHTML =array[4];"
          "document.getElementById(\"PV2\").innerHTML =array[5];"
          "document.getElementById(\"CV2\").innerHTML =array[6];"
          "document.getElementById(\"CM2\").innerHTML =array[7];"

          "document.getElementById(\"ControlOutput\").innerHTML =array[8];"

          
          "};"
          "};"
          "xhttp.open(\"GET\", \"GetProcessData\", true);"
          "xhttp.send();"
          "};"
        
          "</script>"
"</body>"
"</html>";          
 void  handleProcessData(){         
  server.send(200, "text/html", ThermostatDataHTML);
 
}

//##############################################################################################
//### Data request handler  ####################################################################
//##############################################################################################

void handleGetProcessData() {
 String Data = "";
        Data += String(Thermostat.SP) + ";" + String(Thermostat.PV) + ";" + String(Thermostat.CV) + ";" + String(Thermostat.ControlMode) + ";";
        Data += String(Rtl.SP) + ";" + String(Rtl.PV) + ";" + String(Rtl.CV) + ";" + String(Rtl.ControlMode) + ";";
        Data += String(ControlOutput);
        

        
    Serial.println("http request fot controller data");
    server.send(200, "text/plane", Data); 
}
