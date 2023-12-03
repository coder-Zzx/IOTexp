#include <LiquidCrystal.h>
#include <DHT.h>
#include <Bounce2.h>

int DHT11Pin = 9;
int ButtonPin = 8;

DHT dht(DHT11Pin, DHT22);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Bounce2::Button button = Bounce2::Button();

int mode = 0;

byte swordIcon[8][8] = {
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x1F },
  { 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F },
  { 0x00, 0x00, 0x18, 0x1C, 0x1C, 0x1F, 0x1F, 0x1F },
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1F, 0x1F },
  { 0x1F, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00 },
  { 0x1F, 0x1F, 0x1F, 0x1C, 0x1C, 0x18, 0x10, 0x00 },
  { 0X1F, 0x1F, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00 },
};

void setup() {
  // put your setup code here, to run once:
  button.attach(ButtonPin);
  button.interval(50);

  lcd.begin(16, 2);

  lcd.createChar(0, swordIcon[0]);
  lcd.createChar(1, swordIcon[1]);
  lcd.createChar(2, swordIcon[2]);
  lcd.createChar(3, swordIcon[3]);
  lcd.createChar(4, swordIcon[4]);
  lcd.createChar(5, swordIcon[5]);
  lcd.createChar(6, swordIcon[6]);
  lcd.createChar(7, swordIcon[7]);

  attachInterrupt(ButtonPin, changeMode, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  button.update();
  switch (mode) {
    case 0:
      {
        displayInit();
        break;
      }
    case 1:
      {
        displayDHT();
        break;
      }
    case 2:
      {
        displaySword();
        break;
      }
  }
}

void changeMode() {
  mode = (mode + 1) % 3;
  lcd.clear();
}

void displayInit() {
  for (int i = 0; i < 4; ++i) {
    lcd.setCursor(0, 0);
    lcd.print("Initializing...");
    delay(500);
    lcd.clear();
    delay(500);
  }
  lcd.clear();
  delay(200);
  lcd.setCursor(0, 1);
  lcd.print("Hello, World!");
  delay(500);
  for (int i = 0; i < 16; ++i) {
    lcd.scrollDisplayLeft();
    delay(500);
  }
  delay(2000);  // 等待2秒钟
  changeMode();
}

void displayDHT() {
  float temperature = (float)dht.readTemperature();
  float humidity = (float)dht.readHumidity();
  lcd.setCursor(0, 0);
  lcd.print("temperature:");
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print("humidity:");
  lcd.print(humidity);
}

void displaySword() {
  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  for (int i = 0; i < 13; i++) {
    lcd.write(byte(1));
  }
  lcd.write(2);
  lcd.write(3);  // 显示自定义字符0（剑）

  lcd.setCursor(0, 1);
  lcd.write(4);
  for (int i = 0; i < 13; i++) {
    lcd.write(byte(5));
  }
  lcd.write(6);
  lcd.write(7);
}
