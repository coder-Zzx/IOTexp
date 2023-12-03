#include <Bounce2.h>
#define TEST

int column[8] = {A5, 3, 4, 5, 6, 7, 8, 9};
int row[8] = {10, 11, 12, 13, A0, A1, A2, A3};

int mode = 0;
int buttonPin = 2;

Bounce2::Button button = Bounce2::Button();

unsigned char pattern_all_off[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}};

unsigned char pattern_heart[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0}};

unsigned char pattern_Z[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1}};

unsigned char pattern_X[8][8] = {
    {1, 0, 0, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 1}};

void displayPattern(byte pattern[][])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (pattern[i][j] == 1)
            {
                digitalWrite(column[i], HIGH);
                digitalWrite(row[j], LOW);
                delay(1);
                digitalWrite(row[j], HIGH);
                digitalWrite(column[i], LOW);
            }
        }
    }
}

void setup()
{
    Serial.begin(9600);

    button.attach(buttonPin, INPUT_PULLUP);
    button.interval(50);
    attachInterrupt(digitalPinToInterrupt(buttonPin), changeMode, FALLING);

    for (int i = 0; i < 8; i++)
    {
        pinMode(row[i], OUTPUT);
        pinMode(column[i], OUTPUT);
        digitalWrite(row[i], HIGH);
        digitalWrite(column[i], LOW);
    }
}

void loop()
{
    button.update();

    #ifdef TEST
    if (Serial.available() > 0) {
        String inputString = Serial.readStringUntil('\n');

        mode = inputString.toInt();
    }
#endif


    switch (mode)
    {
    case 0:
    {
        displayPattern(pattern_all_off);
        break;
    }

    case 1:
    {
        displayPattern(pattern_Z);
        delay(500);
        displayPattern(pattern_all_off);
        delay(100);
        displayPattern(pattern_Z);
        delay(500);
        displayPattern(pattern_all_off);
        delay(100);
        displayPattern(pattern_X);
        delay(500);
        displayPattern(pattern_all_off);
        delay(100);
        break;
    }

    case 2:
    {
        displayPattern(pattern_heart);
        break;
    }

    default:
        break;
    }

    delay(10);
}

void changeMode()
{
    mode = (mode + 1) % 3;
}