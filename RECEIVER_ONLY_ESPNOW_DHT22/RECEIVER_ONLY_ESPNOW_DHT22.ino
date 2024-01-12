/* ############################################################################################## */
/*                                             ESPNOW                                             */
/* ############################################################################################## */

#include <ESP8266WiFi.h>
#include <espnow.h>


/* ############################################################################################## */
/*                                             DHT22                                              */
/* ############################################################################################## */

#include "DHT.h"
#define sensor DHT22

// PIN D4 = GPIO 2
int dataPin = 2; 
               
// DHT22 initialisieren
DHT dht(dataPin, sensor);  

// Temperatur
float temperature; float humidity;


unsigned long previousMillis  = 0;  
const long interval           = 300000;


// Empfangene Nachricht
typedef struct message {
  char payload[250];
} message;

message messageIn;

void recive(uint8_t * incommingMacAddress, uint8_t *incomingData, uint8_t len) {

  memcpy(&messageIn, incomingData, sizeof(messageIn));
  
  String command = "action:" + String(messageIn.payload);

  // Daten über den seriellen Port weiterleiten
  //Serial.print("Payload: ");
  //Serial.println(messageIn.payload);


  Serial.println(command);

  
}

void setup() {
  
  Serial.begin(115200);

  pinMode(dataPin, INPUT);
  dht.begin(); 
  
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(recive);
}
 
void loop() {

  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    
    previousMillis = currentMillis;
    temperature = dht.readTemperature(); // Die Temperatur des Sensors
    humidity    = dht.readHumidity(); // Die Luftfeuchtigkeit des Sensors

    // Erstellen des Befehlsstrings mit Temperatur und Feuchtigkeit
    String temperatureCommand = "action:http://192.168.0.187:51828/?accessoryId=temperatur1nowgateway&value=" + String(temperature);
    Serial.println(temperatureCommand);
    String humidityCommand = "action:http://192.168.0.187:51828/?accessoryId=humidity1nowgateway&value=" + String(humidity);
    Serial.println(humidityCommand);
    
  }

}
