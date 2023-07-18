#include <Arduino.h>

#define TOTAL_PINS 12

const byte bufferSize = TOTAL_PINS;
char inputBuffer[bufferSize + 1];
int value;
// int pins[] = {15,4,17,18,21,23,13,14,26,25,32,33};
int pins[] = {23,21,17,18,4,15,13,14,25,26,32,33};

void setup() {
  Serial.begin(115200);  // opens serial port, sets data rate to 9600 bps
  // Seta portas como OUTPUTS
  for (int i = 0; i < TOTAL_PINS; i++) {
    pinMode(pins[i], OUTPUT);
    ledcAttachPin(pins[i], i);
    ledcSetup(i, 1000, 3);
  }
}

void loop() {
  ledcWrite(15, 0);
  if (Serial.available() >= TOTAL_PINS) {
    // read the incoming byte:
    byte bytesRead = Serial.readBytesUntil('\n', inputBuffer, bufferSize);

    if (bytesRead == TOTAL_PINS) {
      for (int j = 0; j < TOTAL_PINS; j++) {
        value = inputBuffer[j] - '0';
        ledcWrite(j, value);
      }
    } else {
      Serial.println("Quantidade invalida");
    }
  }
}
