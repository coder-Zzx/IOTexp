#include <DHT.h>
#include <Bounce2.h>

int DHT11Pin = 9;
int ButtonPin = 8;
int LEDPin = 7;
int switchPin = 6;
DHT dht(DHT11Pin, DHT22);
Bounce2::Button button1 = Bounce2::Button();
Bounce2::Button button2 = Bounce2::Button();
int mode = 0;
int onoff = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDPin, OUTPUT);
  button1.attach(ButtonPin, INPUT_PULLUP);
  button1.interval(50);
  button2.attach(switchPin, INPUT_PULLUP);
  button2.interval(50);
}

void loop() {
  // put your main code here, to run repeatedly:
  button1.update();
  button2.update();
  if (button1.pressed()) {
    mode = !mode;
  }

  float temperature = (float)dht.readTemperature();

  if (mode) {
    if (temperature > 5) {
      digitalWrite(LEDPin, HIGH);
    } else {
      digitalWrite(LEDPin, LOW);
    }
  } else {
    if (button2.pressed()) {
      onoff = !onoff;
      digitalWrite(LEDPin, onoff);
    }
  }
}
