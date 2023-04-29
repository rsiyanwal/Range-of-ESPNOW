#include <espnow.h>
#include <ESP8266WiFi.h>

/* Variables */
#define CHANNEL 1
uint8_t RECEIVER_MAC[] = {0xE8, 0xDB, 0x84, 0xE0, 0x4A, 0x46};
byte packetBuffer[250]; 
int packetCount = 0; 
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

/* CallBack function called when data is sent */
void OnDataSent(uint8_t *RECEIVER_MAC, uint8_t sendStatus){
 //Serial.print("\r\nLast Packet Sent Status:\t");
 //Serial.println(sendStatus == 0 ? "Delivery Success" : "Delivery Fail"); 
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the send CallBack
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  // add receiver to peer list
  esp_now_add_peer(RECEIVER_MAC, ESP_NOW_ROLE_SLAVE, CHANNEL, NULL, 0);
  
}

void loop() {
  // generate packet data
  for (int i = 0; i < sizeof(packetBuffer); i++){
    packetBuffer[i] = random(0, 256); // fill buffer with random data
  }

  // send packet
  if (esp_now_send(RECEIVER_MAC, packetBuffer, sizeof(packetBuffer)) == ERR_OK){
    packetCount++;
    //Serial.println("Packet sent: ");
    //Serial.print(packetCount);
  }else{
    Serial.println("Error sending packet");
  }

  if((millis() - lastTime) > timerDelay){
    Serial.print("Packet sent: ");
    Serial.println(packetCount);
    lastTime = millis();
    packetCount = 0;
  }

  delay(10); // delay to avoid flooding network
}
