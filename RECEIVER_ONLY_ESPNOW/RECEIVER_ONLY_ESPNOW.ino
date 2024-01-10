#include <ESP8266WiFi.h>
#include <espnow.h>

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
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(recive);
}
 
void loop() {

}
