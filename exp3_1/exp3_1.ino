int redLED = 2;
int yellowLED = 3;
int greenLED = 4;
int gateLED = 5;
int pirSensor = 6;

void LEDBling(int pinLED) {
  for (int i = 0; i < 5; i++) {
    digitalWrite(pinLED, HIGH);
    delay(100);
    digitalWrite(pinLED, LOW);
    delay(100);
  }
}

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(gateLED, OUTPUT);
  pinMode(pirSensor, INPUT);


  digitalWrite(redLED, HIGH);
  digitalWrite(gateLED, LOW);
}

void loop() {
  digitalWrite(yellowLED, HIGH);
  delay(3000);
  LEDBling(yellowLED);
  digitalWrite(yellowLED, LOW);


  digitalWrite(greenLED, HIGH);
  
  for (int i = 0; i < 300; i++) {
    if (digitalRead(pirSensor) == HIGH) {
      digitalWrite(gateLED, HIGH);
    } else {
      digitalWrite(gateLED, LOW);
    }

    delay(10);
  }

  digitalWrite(gateLED, LOW);
  LEDBling(greenLED);
  digitalWrite(greenLED, LOW);


  digitalWrite(redLED, HIGH);
  delay(3000);
  LEDBling(redLED);
  digitalWrite(redLED, LOW);
}