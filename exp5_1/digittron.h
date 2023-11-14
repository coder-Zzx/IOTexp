#ifndef DIGITTRON_H
#define DIGITTRON_H

int digitCode[] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90 };

void displayNum(int num, int LEDPins[]) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(LEDPins[i], bitRead(num, i));
  }
}

#endif