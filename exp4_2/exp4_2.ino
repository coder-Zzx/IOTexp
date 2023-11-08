int lightSensorPin = A0;
int ledPin = 9;
int lightValue = 0;
int brightness = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(lightSensorPin, INPUT);
}

void loop() {
  lightValue = analogRead(lightSensorPin);

  brightness = map(lightValue, 0, 1023, 0, 255);

  brightness = constrain(brightness, 0, 255);

  analogWrite(ledPin, brightness);

  delay(10);
}