#include <Arduino.h>
#include <WiFi.h>
#include "esp_wifi.h"

#define TOTAL_PINS 12
#define USE_WIFI true

const char bufferSize = TOTAL_PINS;
char inputBuffer[bufferSize + 1];
// int pins[] = {15,4,17,18,21,23,13,14,26,25,32,33};
int pins[] = {23,21,17,18,4,15,13,14,25,26,32,33};

const char* ssid = "NET_2GA9619C";
const char* password = "51A9619C";

const uint ServerPort = 23;
WiFiServer server(ServerPort);

int value;

void setup(){

  Serial.begin(9600);

  if(USE_WIFI){
    // Connect to Wi-Fi network with SSID and password
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
  }

  // Set pins as OUTPUTS
  for (int i = 0; i < TOTAL_PINS; i++) {
    pinMode(pins[i], OUTPUT);
    ledcAttachPin(pins[i], i);
    ledcSetup(i, 1000, 3);
  }

}

void loop(){

  ledcWrite(15, 0);

  if(USE_WIFI){
    WiFiClient client = server.available();
    if(client){
      while (client.connected()) {  
        if (client.available() >= TOTAL_PINS) {
          //Read the incoming byte:
          byte bytesRead = client.readBytesUntil('\n', inputBuffer, bufferSize);
          if (bytesRead == TOTAL_PINS) {
            for (int j = 0; j < TOTAL_PINS; j++) {
              value = inputBuffer[j] - '0';
              ledcWrite(j, value);
            }
          } else {
            Serial.println("Invalid message size");
          }
          
        }
      }
      // Close the connection
      client.stop();
    }

  } else {
    if (Serial.available() >= TOTAL_PINS) {
      //Read the incoming byte:
      byte bytesRead = Serial.readBytesUntil('\n', inputBuffer, bufferSize);

      if (bytesRead == TOTAL_PINS) {
        for (int j = 0; j < TOTAL_PINS; j++) {
          value = inputBuffer[j] - '0';
          ledcWrite(j, value);
        }
      } else {
        Serial.println("Invalid message size");
      }
    }
  }


}



// void loop() {
//   ledcWrite(15, 0);
//   if (Serial.available() >= TOTAL_PINS) {
//     // read the incoming byte:
//     byte bytesRead = Serial.readBytesUntil('\n', inputBuffer, bufferSize);

//     if (bytesRead == TOTAL_PINS) {
//       for (int j = 0; j < TOTAL_PINS; j++) {
//         value = inputBuffer[j] - '0';
//         ledcWrite(j, value);
//       }
//     } else {
//       Serial.println("Quantidade invalida");
//     }
//   }
// }