#include <espnow.h>
#include <ESP8266WiFi.h>

#define CHANNEL 1 

byte packetBuffer[250]; 
int packetCount = 0; 
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

/* Callback Function that will be executed when data is received */
void OnDataRecv(uint8_t *mac, uint8_t *data, uint8_t len){
  memcpy(packetBuffer, data, sizeof(packetBuffer));
  packetCount++;
  //Serial.println("Packet received: ");
  //Serial.println(packetCount);
  if((millis() - lastTime) > timerDelay){
    Serial.print("Packet received: ");
    Serial.println(packetCount);
    lastTime = millis();
    packetCount = 0;
  }
}

void setup(){
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ERR_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // set ESP-NOW receive callback
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop(){

}
