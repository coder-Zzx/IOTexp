#include "digittron.h"
#include "LM35.h"

int LEDPins[] = { 4, 5, 6, 7, 8, 9, 10, 11 };
int temperaturePin = A0;
int buzzlePin = 2;
LM35 lm35 = LM35(temperaturePin);

void setup() {
  // put your setup code here, to run once:
  for (int LED = 0; LED < 8; LED++) {
    pinMode(LEDPins[LED], INPUT);
  }

  pinMode(buzzlePin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int temperature;
#ifdef TEST
  if (Serial.available() > 0) {
    String inputString = Serial.readStringUntil('\n');

    temperature = inputString.toInt();
#endif

#ifndef TEST
    temperature = lm35.readCelsius();
#endif

    if (temperature < 10) {
      displayNum(1, LEDPins);
      digitalWrite(buzzlePin, LOW);
    } else if (temperature >= 10 && temperature < 40) {
      displayNum(2, LEDPins);
      digitalWrite(buzzlePin, LOW);
    } else if (temperature >= 40) {
      displayNum(3, LEDPins);
      digitalWrite(buzzlePin, HIGH);
    }
  }