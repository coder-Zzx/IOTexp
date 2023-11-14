#include <DHT.h>
#include <Bounce2.h>
#include <IRremote.h>

int IRRecievePin = 11;
int DHT11Pin = 9;
int LEDPin = 7;
int switchPin = 6;
DHT dht(DHT11Pin, DHT22);
Bounce2::Button button = Bounce2::Button();
int mode = 0;
int onoff = 0;
decode_results results;

IRrecv irrecv(IRRecievePin);

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDPin, OUTPUT);
  irrecv.enableIRIn();
  button.attach(switchPin, INPUT_PULLUP);
  button.interval(50);
}

void loop() {
  // put your main code here, to run repeatedly:
  button.update();
  if (irrecv.decode(&results)) {
    if (results.value == 0x111111) {
      mode = 1;
    } else if (results.value == 0x222222) {
      mode = 0;
    } else {
      mode = !mode;
    }
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
  irrecv.resume();
  delay(100);
}
