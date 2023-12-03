#include <LiquidCrystal.h>
#include <Keypad.h>
#include <EEPROM.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // LCD初始化

const int switchPin = 1; // 开关切换模式的引脚
const int vibrationPin = 13; // 震动传感器的引脚
const int warningLed = A4; // 预警灯的引脚

const char passwordLength = 6;
char password[passwordLength + 1] = "123456"; // 初始密码

char enteredPassword[passwordLength + 1];
char newPassword[passwordLength + 1];

const byte ROW_NUM    = 4; // 行数
const byte COLUMN_NUM = 4; // 列数
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; // 连接行脚的引脚
byte pin_column[COLUMN_NUM] = {A0, A1, A2, A3}; // 连接列脚的引脚
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

enum Mode {
  ENTER_PASSWORD,
  CHANGE_PASSWORD
};

Mode currentMode = ENTER_PASSWORD;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Enter Password");
  
  pinMode(switchPin, INPUT);
  pinMode(vibrationPin, INPUT);
  pinMode(warningLed, OUTPUT);
}

void loop() {
  switch (currentMode) {
    case ENTER_PASSWORD:
      enterPasswordMode();
      break;
    case CHANGE_PASSWORD:
      changePasswordMode();
      break;
  }
}

void enterPasswordMode() {
  char key = keypad.getKey();
  if (key) {
    if (key == '#') {
      if (checkPassword()) {
        lcd.clear();
        lcd.print("Access Granted");
        delay(2000);
        lcd.clear();
      } else {
        activateWarning();
        delay(2000);
        lcd.clear();
      }
      clearEnteredPassword();
    } else if (key == '*') {
      clearEnteredPassword();
      lcd.clear();
      lcd.print("Enter Password");
      lcd.setCursor(0, 1);
    } else {
      addToEnteredPassword(key);
    }
  }

  if (digitalRead(switchPin) == HIGH) {
    currentMode = CHANGE_PASSWORD;
    lcd.clear();
    lcd.print("Enter New Password");
    lcd.setCursor(0, 1);
    delay(1000);
    clearEnteredPassword();
  }

  if (digitalRead(vibrationPin) == HIGH) {
    activateWarning();
    delay(2000);
    lcd.clear();
  }
}

void changePasswordMode() {
  char key = keypad.getKey();
  if (key) {
    if (key == '#') {
      updatePassword();
      lcd.clear();
      lcd.print("Password Changed");
      delay(2000);
      lcd.clear();
      currentMode = ENTER_PASSWORD;
      lcd.print("Enter Password");
      lcd.setCursor(0, 1);
    } else if (key == '*') {
      clearEnteredPassword();
      lcd.clear();
      lcd.print("Enter New Password");
      lcd.setCursor(0, 1);
    } else {
      addToEnteredPassword(key);
    }
  }

  if (digitalRead(switchPin) == HIGH) {
    currentMode = ENTER_PASSWORD;
    lcd.clear();
    lcd.print("Enter Password");
    delay(1000);
    clearEnteredPassword();
  }

  if (digitalRead(vibrationPin) == HIGH) {
    activateWarning();
    delay(2000);
    lcd.clear();
  }
}

void addToEnteredPassword(char key) {
  if (strlen(enteredPassword) < passwordLength) {
    strcat(enteredPassword, &key);
    lcd.print('*');
  }
}

void clearEnteredPassword() {
  memset(enteredPassword, 0, sizeof(enteredPassword));
}

void activateWarning() {
  lcd.clear();
  lcd.print("Intruder Alert!");
  for (int i = 0; i < 30; i++) {
    digitalWrite(warningLed, HIGH);
    delay(100);
    digitalWrite(warningLed, LOW);
    delay(100);
  }
  lcd.clear();
}

bool checkPassword() {
  return strcmp(enteredPassword, password) == 0;
}

void updatePassword() {
  strncpy(password, enteredPassword, passwordLength);
  EEPROM.put(0, newPassword);
  clearEnteredPassword();
  lcd.clear();
}