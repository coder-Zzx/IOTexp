#include <EEPROM.h>
#include <SPI.h>
#include <Bounce2.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

#define VIBRATION_SENSOR_PIN 2
#define LED_PIN 5
#define RECORD_BUTTON_PIN 3

#define EEPROM_START_ADDR 0
#define CARD_SIZE 4

bool authorized = false;
int mode = 0;

Bounce2::Button button = Bounce2::Button();

void setup() {
  button.attach(RECORD_BUTTON_PIN, INPUT_PULLUP);
  button.interval(50);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(VIBRATION_SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(RECORD_BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(LED_PIN, LOW);

  attachInterrupt(digitalPinToInterrupt(RECORD_BUTTON_PIN), change, FALLING);

  for (byte i = 0; i < CARD_SIZE; i++) {
    Serial.println(EEPROM.read(EEPROM_START_ADDR + i));
  }

  Serial.print("current mode:");
  Serial.println(mode);
}

void loop() {

  //  button.update();

  if (!mode) {
    recordCard();
    delay(1000);
  } else {
    if (checkCard()) {
      authorized = true;
      Serial.println("Authorized access.");
    } else if (detectIntrusion()) {
      authorized = false;
      Serial.println(detectIntrusion());
      if (!authorized) {
        activateAlarm();
      }
    } else {
      authorized = false;
    }
  }

  mfrc522.PICC_HaltA();


  mfrc522.PCD_StopCrypto1();
  mfrc522.PCD_Reset();

  SPI.begin();
  mfrc522.PCD_Init();
  delay(1000);
}

void recordCard() {

  Serial.println("starting record card!");
  if ((mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())) {
    Serial.println("rrrr");
    byte cardID[CARD_SIZE];
    Serial.println("recording card UID:");
    for (byte i = 0; i < CARD_SIZE; i++) {
      cardID[i] = mfrc522.uid.uidByte[i];
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }

    for (byte i = 0; i < CARD_SIZE; i++) {
      EEPROM.write(EEPROM_START_ADDR + i, cardID[i]);
    }
  }
}

bool checkCard() {
  bool flag = false;
  Serial.println("checking card UID:");
  if ((mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())) {
    byte cardID[CARD_SIZE];
    Serial.println("cccc");
    for (byte i = 0; i < CARD_SIZE; i++) {
      cardID[i] = mfrc522.uid.uidByte[i];
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }


    for (byte i = 0; i < CARD_SIZE; i++) {
      if (EEPROM.read(EEPROM_START_ADDR + i) != cardID[i]) {
        flag = false;

        return false;
      }
    }

    flag = true;


    return flag;
  }
  return false;
}

bool detectIntrusion() {
  return digitalRead(VIBRATION_SENSOR_PIN) == HIGH;
}

void activateAlarm() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("wrong card!!!");
  Serial.println("wrong card!!!");
  Serial.println("wrong card!!!");
  delay(2000);
  digitalWrite(LED_PIN, LOW);
}

void change() {
  mode = !mode;
  Serial.println("mode changed!!!");
  Serial.print("currently mode");
  Serial.println(mode);
}
