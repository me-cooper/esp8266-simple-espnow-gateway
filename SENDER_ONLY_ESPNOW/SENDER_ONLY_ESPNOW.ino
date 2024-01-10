// AKTUELL DER SENDER

#include <ESP8266WiFi.h>
#include <espnow.h>


// Trage hier die MAC-Adresse des Empfaengers ein 
uint8_t macAddress[] = {0x8C, 0xAA, 0xB5, 0x0E, 0x03, 0x2A};

// struct welches übertragen wird
typedef struct message {
  char payload[250];
} message;


// Nachricht welche gesendet wird
message messageOut;

// Wird aufgerufen wenn die Nachricht gesendet wurde
void messageSend(uint8_t *macAddress, uint8_t status) {
  if (status == 0){
    Serial.println("Erfolgreich gesendet");
  } else {
    Serial.println("Fehler beim senden");
  }
}


void setup() {
  
  // Starte seriellen Monitor
  Serial.begin(115200);
 
  // Setze Geraet in Station mode
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) { Serial.println("Error initializing ESP-NOW"); }

  // Rolle wird auf COMBO gesetzt, da wir senden umd empfangen.
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
 
  esp_now_add_peer(macAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);

  esp_now_register_send_cb(messageSend);
  

  char thisCommand[250] = "http://192.168.0.187:51828/?accessoryId=nachtlichttrigger1&state=true";
  memcpy(&messageOut.payload, thisCommand, sizeof(thisCommand));

  // Sende Nachricht ueber ESP-NOW
  esp_now_send(macAddress, (uint8_t *) &messageOut, sizeof(messageOut));

  ESP.deepSleep(0);

}
 
void loop() {
  
}
