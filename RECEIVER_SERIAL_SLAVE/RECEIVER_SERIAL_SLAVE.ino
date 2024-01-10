// ESPNOW-HTTP-Slave

#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


HTTPClient sender;
WiFiClient wifiClient;


void setup() {

  Serial.begin(115200);

  WiFiManager wifiManager;

  bool res = wifiManager.autoConnect("ESPNOW-WIFI-GATEWAY","ESPNOW-WIFI-GATEWAY");
  
  if(!res) {
    Serial.println("Failed to connect");
    ESP.restart(); 
  } 

  Serial.println("WLAN-Verbindung hergestellt");
    

}



void makeAPIcall(String endpoint){
  if (sender.begin(wifiClient, endpoint)) {

    // HTTP-Code der Response speichern
    int httpCode = sender.GET();
   

    if (httpCode > 0) {
      
      // Anfrage wurde gesendet und Server hat geantwortet
      // Info: Der HTTP-Code für 'OK' ist 200
      if (httpCode == HTTP_CODE_OK) {

        // Hier wurden die Daten vom Server empfangen

        // String vom Webseiteninhalt speichern
        String payload = sender.getString();

        // Hier kann mit dem Wert weitergearbeitet werden
       // ist aber nicht unbedingt notwendig
        Serial.println(payload);
        
      }
      
    }else{

      // Falls HTTP-Error
      Serial.printf("HTTP-Error: ", sender.errorToString(httpCode).c_str());
      Serial.println();

    }

    // Wenn alles abgeschlossen ist, wird die Verbindung wieder beendet
    sender.end();
    
  }else {

    Serial.printf("HTTP-Verbindung konnte nicht hergestellt werden!");

  }

}




void loop() {
  
  if (Serial.available()) {
    String receivedString = Serial.readString();
    receivedString.trim();
    
    // Überprüfen, ob der String "action:" enthält
    int actionIndex = receivedString.indexOf("action:");
    if (actionIndex != -1) {
      // Entfernen Sie "action:" und alle Zeichen davor
      receivedString = receivedString.substring(actionIndex + strlen("action:"));

      Serial.println(receivedString);

      makeAPIcall(receivedString);

    }
  }
}
