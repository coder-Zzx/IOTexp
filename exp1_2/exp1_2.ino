#include<Bounce2.h>

int ledpin = 11;
int inpin = 7;
int val = LOW;
Bounce2::Button button = Bounce2::Button();


void setup() {
  pinMode(ledpin, OUTPUT);
  pinMode(inpin, INPUT);
  button.attach(inpin, INPUT_PULLUP);
  button.interval(50);
}

void loop() {
  button.update();
  
  if (button.pressed()) {
    val = !val;
    digitalWrite(ledpin, val);
  }
}
