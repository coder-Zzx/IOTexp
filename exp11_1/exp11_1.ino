// #include <Bounce2.h>
#include <Keypad.h>
#include <OneButton.h>
// #define TEST

bool manualMode = true;
bool longPressed = false;

int touchPin = 2;
int redPin = 3;
int greenPin = 11;
int bluePin = 5;
int trigPin = 13;
int echoPin = 12;

// Bounce2::Button button = Bounce2::Button();
OneButton button(touchPin, true);

const byte ROW_NUM = 4;     // 行数
const byte COLUMN_NUM = 4;  // 列数
char keys[ROW_NUM][COLUMN_NUM] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte pin_rows[ROW_NUM] = { 9, 8, 7, 10 };           // 连接行脚的引脚
byte pin_column[COLUMN_NUM] = { A0, A1, A2, A3 };  // 连接列脚的引脚
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(touchPin, INPUT);
  button.attachLongPressStart(changeMode);
  button.attachLongPressStop(longPressStopHandler);
  // button.attach(touchPin, INPUT_PULLUP);
  // button.interval(50);
}

void loop() {
  // put your main code here, to run repeatedly:
  // button.upgrade();
  button.tick();
  Serial.print("touchPin: ");
  Serial.println(digitalRead(touchPin));
  // if (digitalRead(touchPin) == HIGH) {
  //   delay(1000);
  //   if (digitalRead(touchPin) == HIGH) {
  //     manualMode = !manualMode;
  //     if (manualMode) {
  //       Serial.println("changed to manual mode");
  //     } else {
  //       Serial.println("changed to auto mode");
  //     }
  //   }
  // }

  if (manualMode) {
    handleManualMode();
  } else {
    handleAutoMode();
  }
}

void handleManualMode() {
  char key = keypad.getKey();
  if (key) {
    setColor(0, 0, 0);
    if (key == '1') {
      setColor(255, 0, 0);
    } else if (key == '2') {
      for (int i = 0; i < 255; i += 5) {
        setColor(0, 0, i);
        delay(10);
      }
    } else if (key == '3') {
      for (int i = 0; i < 255; i += 5) {
        digitalWrite(redPin, i * 3 < 255 ? i * 3 : 255);
        digitalWrite(bluePin, i * 2 < 255 ? i * 2 : 255);
        digitalWrite(greenPin, i);
      }
    }
  }
}

void handleAutoMode() {
  button.tick();
  Serial.print("distance: ");
  Serial.println(getDistance());
  int distance = map(getDistance(), 2, 450, 0, 255);
  if (distance > 20) {
    setColor(255, 0, 0);
  } else if (distance < 10 && distance > 3) {
    setColor(0, -36.428 * distance + 364.285, 36.428 * distance - 109.285);
  } else if (distance >= 10 && distance < 20) {
    setColor(36.428 * distance - 109.285, 0, -36.428 * distance + 364.285);
  } else {
    Serial.println("wrong distance!");
    setColor(0, 255, 0);
  }
}

int getDistance() {
#ifndef TEST
  long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
#endif

#ifdef TEST
  int dis;
  if (Serial.available() > 0) {
    String inputString = Serial.readStringUntil('\n');

    int dis = inputString.toInt();
  }
  return dis;
#endif
}

void setColor(int redVal, int greenVal, int blueVal) {
  analogWrite(redPin, redVal);
  analogWrite(greenPin, greenVal);
  analogWrite(bluePin, blueVal);
}

void changeMode() {
  if (!longPressed) {
    manualMode = !manualMode;
    setColor(0, 0, 0);
    if (manualMode) {
      Serial.println("changed to manual mode");
    } else {
      Serial.println("changed to auto mode");
    }
    longPressed = true;
  }
}

void longPressStopHandler() {
  longPressed = false;
}
// #include <Bounce2.h>
#include <Keypad.h>
#include <OneButton.h>
// #define TEST

bool manualMode = true;
bool longPressed = false;

int touchPin = 2;
int redPin = 3;
int greenPin = 11;
int bluePin = 5;
int trigPin = 13;
int echoPin = 12;

// Bounce2::Button button = Bounce2::Button();
OneButton button(touchPin, true);

const byte ROW_NUM = 4;     // 行数
const byte COLUMN_NUM = 4;  // 列数
char keys[ROW_NUM][COLUMN_NUM] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte pin_rows[ROW_NUM] = { 9, 8, 7, 10 };           // 连接行脚的引脚
byte pin_column[COLUMN_NUM] = { A0, A1, A2, A3 };  // 连接列脚的引脚
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(touchPin, INPUT);
  button.attachLongPressStart(changeMode);
  button.attachLongPressStop(longPressStopHandler);
  // button.attach(touchPin, INPUT_PULLUP);
  // button.interval(50);
}

void loop() {
  // put your main code here, to run repeatedly:
  // button.upgrade();
  button.tick();
  Serial.print("touchPin: ");
  Serial.println(digitalRead(touchPin));
  // if (digitalRead(touchPin) == HIGH) {
  //   delay(1000);
  //   if (digitalRead(touchPin) == HIGH) {
  //     manualMode = !manualMode;
  //     if (manualMode) {
  //       Serial.println("changed to manual mode");
  //     } else {
  //       Serial.println("changed to auto mode");
  //     }
  //   }
  // }

  if (manualMode) {
    handleManualMode();
  } else {
    handleAutoMode();
  }
}

void handleManualMode() {
  char key = keypad.getKey();
  if (key) {
    setColor(0, 0, 0);
    if (key == '1') {
      setColor(255, 0, 0);
    } else if (key == '2') {
      for (int i = 0; i < 255; i += 5) {
        setColor(0, 0, i);
        delay(10);
      }
    } else if (key == '3') {
      for (int i = 0; i < 255; i += 5) {
        digitalWrite(redPin, i * 3 < 255 ? i * 3 : 255);
        digitalWrite(bluePin, i * 2 < 255 ? i * 2 : 255);
        digitalWrite(greenPin, i);
      }
    }
  }
}

void handleAutoMode() {
  button.tick();
  Serial.print("distance: ");
  Serial.println(getDistance());
  int distance = map(getDistance(), 2, 450, 0, 255);
  if (distance > 20) {
    setColor(255, 0, 0);
  } else if (distance < 10 && distance > 3) {
    setColor(0, -36.428 * distance + 364.285, 36.428 * distance - 109.285);
  } else if (distance >= 10 && distance < 20) {
    setColor(36.428 * distance - 109.285, 0, -36.428 * distance + 364.285);
  } else {
    Serial.println("wrong distance!");
    setColor(0, 255, 0);
  }
}

int getDistance() {
#ifndef TEST
  long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
#endif

#ifdef TEST
  int dis;
  if (Serial.available() > 0) {
    String inputString = Serial.readStringUntil('\n');

    int dis = inputString.toInt();
  }
  return dis;
#endif
}

void setColor(int redVal, int greenVal, int blueVal) {
  analogWrite(redPin, redVal);
  analogWrite(greenPin, greenVal);
  analogWrite(bluePin, blueVal);
}

void changeMode() {
  if (!longPressed) {
    manualMode = !manualMode;
    setColor(0, 0, 0);
    if (manualMode) {
      Serial.println("changed to manual mode");
    } else {
      Serial.println("changed to auto mode");
    }
    longPressed = true;
  }
}

void longPressStopHandler() {
  longPressed = false;
}
// #include <Bounce2.h>
#include <Keypad.h>
#include <OneButton.h>
// #define TEST

bool manualMode = true;
bool longPressed = false;

int touchPin = 2;
int redPin = 3;
int greenPin = 11;
int bluePin = 5;
int trigPin = 13;
int echoPin = 12;

// Bounce2::Button button = Bounce2::Button();
OneButton button(touchPin, true);

const byte ROW_NUM = 4;     // 行数
const byte COLUMN_NUM = 4;  // 列数
char keys[ROW_NUM][COLUMN_NUM] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte pin_rows[ROW_NUM] = { 9, 8, 7, 10 };           // 连接行脚的引脚
byte pin_column[COLUMN_NUM] = { A0, A1, A2, A3 };  // 连接列脚的引脚
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(touchPin, INPUT);
  button.attachLongPressStart(changeMode);
  button.attachLongPressStop(longPressStopHandler);
  // button.attach(touchPin, INPUT_PULLUP);
  // button.interval(50);
}

void loop() {
  // put your main code here, to run repeatedly:
  // button.upgrade();
  button.tick();
  Serial.print("touchPin: ");
  Serial.println(digitalRead(touchPin));
  // if (digitalRead(touchPin) == HIGH) {
  //   delay(1000);
  //   if (digitalRead(touchPin) == HIGH) {
  //     manualMode = !manualMode;
  //     if (manualMode) {
  //       Serial.println("changed to manual mode");
  //     } else {
  //       Serial.println("changed to auto mode");
  //     }
  //   }
  // }

  if (manualMode) {
    handleManualMode();
  } else {
    handleAutoMode();
  }
}

void handleManualMode() {
  char key = keypad.getKey();
  if (key) {
    setColor(0, 0, 0);
    if (key == '1') {
      setColor(255, 0, 0);
    } else if (key == '2') {
      for (int i = 0; i < 255; i += 5) {
        setColor(0, 0, i);
        delay(10);
      }
    } else if (key == '3') {
      for (int i = 0; i < 255; i += 5) {
        digitalWrite(redPin, i * 3 < 255 ? i * 3 : 255);
        digitalWrite(bluePin, i * 2 < 255 ? i * 2 : 255);
        digitalWrite(greenPin, i);
      }
    }
  }
}

void handleAutoMode() {
  button.tick();
  Serial.print("distance: ");
  Serial.println(getDistance());
  int distance = map(getDistance(), 2, 450, 0, 255);
  if (distance > 20) {
    setColor(255, 0, 0);
  } else if (distance < 10 && distance > 3) {
    setColor(0, -36.428 * distance + 364.285, 36.428 * distance - 109.285);
  } else if (distance >= 10 && distance < 20) {
    setColor(36.428 * distance - 109.285, 0, -36.428 * distance + 364.285);
  } else {
    Serial.println("wrong distance!");
    setColor(0, 255, 0);
  }
}

int getDistance() {
#ifndef TEST
  long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
#endif

#ifdef TEST
  int dis;
  if (Serial.available() > 0) {
    String inputString = Serial.readStringUntil('\n');

    int dis = inputString.toInt();
  }
  return dis;
#endif
}

void setColor(int redVal, int greenVal, int blueVal) {
  analogWrite(redPin, redVal);
  analogWrite(greenPin, greenVal);
  analogWrite(bluePin, blueVal);
}

void changeMode() {
  if (!longPressed) {
    manualMode = !manualMode;
    setColor(0, 0, 0);
    if (manualMode) {
      Serial.println("changed to manual mode");
    } else {
      Serial.println("changed to auto mode");
    }
    longPressed = true;
  }
}

void longPressStopHandler() {
  longPressed = false;
}
