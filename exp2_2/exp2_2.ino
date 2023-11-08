#include<Bounce2.h>

int ledpin[6] = {2, 3, 4, 5, 6, 7};
int inpin = 11;
int val;
int mode = 1;
Bounce2::Button button = Bounce2::Button();

void shutdown() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledpin[i], LOW);
  }
}

void allon();
void rundown() {
  button.update();
  if (button.pressed()) {
    mode = (mode + 1) % 3;
  }
  if (mode == 2) {
    allon();
  }
  else if (mode == 0) {
    shutdown();
  }
for (int i = 0; i < 6; i++) {
  button.update();
  if (button.pressed()) {
    mode = (mode + 1) % 3;
  }
  if (mode == 2) {
    allon();
  }
  else if (mode == 0) {
    shutdown();
  }
  shutdown();
  digitalWrite(ledpin[i], HIGH);
  delay(50);
}
for (int i = 5; i >= 0; i--) {
  button.update();
  if (button.pressed()) {
    mode = (mode + 1) % 3;
  }
  if (mode == 2) {
    allon();
  }
  else if (mode == 0) {
    shutdown();
  }
  shutdown();
  digitalWrite(ledpin[i], HIGH);
  delay(50);
}
}

void allon() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledpin[i], HIGH);
  }
}


void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(ledpin[i], OUTPUT);
  }
  button.attach(inpin, INPUT_PULLUP);
  button.interval(5);
}

void loop() {
  button.update();
  if (button.pressed()) {
    mode = (mode + 1) % 3;

  }
  switch (mode) {
    case 0: {
        shutdown();
        break;
      }
    case 1: {
        rundown();
        break;
      }
    case 2: {
        allon();
        break;
      }
  }
}

