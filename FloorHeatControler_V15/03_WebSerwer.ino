void handleRoot() {
  String message ="<html>";
      message += "<head> <meta charset=\"UTF-8\"></head>";
      message += "<h2>Sterowanie ogrzewania podlogowego</h2>";
      message += "<h3><em>Ustawienia systemowe:</em></h3>";
      message += "<ul>";
      message += "<li><a href=/wifi>Ustawienia wi-fi</a></li>";
      message += "<li><a href=/mqtt>Ustawienia serwera MQTT</a></li>";
      message += "</ul>";
      message += "<h3><em>Strefy grzewcze:</em></h3>";
      message += "<ul>";
      message += "<li><a href=/zonedata>Dane z termostatów</a></li>";
      message += "<li><a href=/pump>Sterowanie pompy mieszacza</a></li>";    
      message += "</ul>";
      message += "<p>&nbsp;</p>";
      message += "<p>&nbsp;</p>";
      message += "<p>&nbsp;</p> ";
      message += "</html>";
 
  server.send(200, "text/html", message);
  
}







void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
