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

"<h2>Dane z termostatów</h2>"

"<table>"
  "<tr>"
    "<th>Strefa</th>"
    "<th>SP [°C]</th>"
    "<th>PV [°C]</th>"
    "<th>CV [%]</th>"
    "<th>Tryb pracy</th>"
    "<th> </th>"
  "</tr>"
  "<tr>"
    "<td>Strefa 1</td>"
    "<td><span id=\"SP1\">x</span></td>"
    "<td><span id=\"PV1\">x</span></td>"
    "<td><span id=\"CV1\">x</span></td>"
    "<td><span id=\"CM1\">x</span></td>"
    "<td><form method=\"get\" action=\"/tSp1\"><button type=\"submit\">Nastawy</button></form></td>"
  "</tr>"
  "<tr>"
    "<td>Strefa 2</td>"
    "<td><span id=\"SP2\">x</span></td>"
    "<td><span id=\"PV2\">x</span></td>"
    "<td><span id=\"CV2\">x</span></td>"
    "<td><span id=\"CM2\">x</span></td>"
    "<td><form method=\"get\" action=\"/tSp2\"><button type=\"submit\">Nastawy</button></form></td>"
  "</tr>"
  "<tr>"
    "<td>Strefa 3</td>"
    "<td><span id=\"SP3\">x</span></td>"
    "<td><span id=\"PV3\">x</span></td>"
    "<td><span id=\"CV3\">x</span></td>"
    "<td><span id=\"CM3\">x</span></td>"
    "<td><form method=\"get\" action=\"/tSp3\"><button type=\"submit\">Nastawy</button></form></td>"
  "</tr>"
  "<tr>"
    "<td>Strefa 4</td>"
    "<td><span id=\"SP4\">x</span></td>"
    "<td><span id=\"PV4\">x</span></td>"
    "<td><span id=\"CV4\">x</span></td>"
    "<td><span id=\"CM4\">x</span></td>"
    "<td><form method=\"get\" action=\"/tSp4\"><button type=\"submit\">Nastawy</button></form></td>"
  "</tr>"
  "<tr>"
    "<td>Strefa 5</td>"
    "<td><span id=\"SP5\">x</span></td>"
    "<td><span id=\"PV5\">x</span></td>"
    "<td><span id=\"CV5\">x</span></td>"
    "<td><span id=\"CM5\">x</span></td>"
    "<td><form method=\"get\" action=\"/tSp5\"><button type=\"submit\">Nastawy</button></form></td>"
  "</tr>"
  
"</table>"
//"<br><a href=\"/\">Menu</A>";
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

          "document.getElementById(\"SP3\").innerHTML =array[8];"
          "document.getElementById(\"PV3\").innerHTML =array[9];"
          "document.getElementById(\"CV3\").innerHTML =array[10];"
          "document.getElementById(\"CM3\").innerHTML =array[11];"

          "document.getElementById(\"SP4\").innerHTML =array[12];"
          "document.getElementById(\"PV4\").innerHTML =array[13];"
          "document.getElementById(\"CV4\").innerHTML =array[14];"
          "document.getElementById(\"CM4\").innerHTML =array[15];"

          "document.getElementById(\"SP5\").innerHTML =array[16];"
          "document.getElementById(\"PV5\").innerHTML =array[17];"
          "document.getElementById(\"CV5\").innerHTML =array[18];"
          "document.getElementById(\"CM5\").innerHTML =array[19];"
          "};"
          "};"
          "xhttp.open(\"GET\", \"GetProcessData\", true);"
          "xhttp.send();"
          "};"
        
          "</script>"
"</body>"
"</html>";          
 void  handleZoneData(){         
  server.send(200, "text/html", ThermostatDataHTML);
 
}

//##############################################################################################
//### Data request handler  ####################################################################
//##############################################################################################

void handleGetProcessData() {
 String Data = "";
    for (int Idx = 1; Idx <= 5; Idx++){ 
       Data += String(Thermostat[Idx].SP) + ";" + String(Thermostat[Idx].PV) + ";" + String(Thermostat[Idx].CV) + ";" + String(Thermostat[Idx].ControlMode) + ";";
        };
    Serial.println("http request fot thermostat data");
    server.send(200, "text/plane", Data); //Send ADC value only to client ajax request
}
