#ifndef LM35_H
#define LM35_H

class LM35 {
private:
  int pin;
  void init(int _pin) {
    this->pin = _pin;
    pinMode(this->pin, 0);
  }

public:
  LM35(int _pin) {
    init(_pin);
  }

  double readCelsius() {
    int IOInput = analogRead(this->pin);
    double temperature = IOInput * 5 * 100 / 1024;
    return temperature;
  }

  double readFarenheit() {
    return readCelsius() * 1.8 + 32;
  }
};

#endif