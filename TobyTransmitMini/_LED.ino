#define RED_LED_PIN 9
#define BLUE_LED_PIN 8

void initIndicatorLeds()
{
    pinMode(BLUE_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);

    ledStartupSequence();
}

void ledStartupSequence()
{
    // crazyPurpleDelayThing();
}

void lightRedLED()
{
    analogWrite(RED_LED_PIN, map(settingLEDBrightness, 0, 100, 0, 255));
    digitalWrite(BLUE_LED_PIN, LOW);
}

void lightBlueLED()
{
    analogWrite(BLUE_LED_PIN, map(settingLEDBrightness, 0, 100, 0, 255));
    digitalWrite(RED_LED_PIN, LOW);
}

void lightPurpleLED()
{
    float purpleLEDred = 5 * ((float)settingLEDBrightness / 100);
    float purpleLEDblue = 255 * ((float)settingLEDBrightness / 100);
    // if (purpleLEDblue < 145)
    // {
    //     purpleLEDblue = 145;
    // }

    analogWrite(RED_LED_PIN, (int)purpleLEDred);
    analogWrite(BLUE_LED_PIN, (int)purpleLEDblue);
}

void turnOffLED()
{
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
}

void crazyPurpleDelayThing()
{
    analogWrite(RED_LED_PIN, 10);
    analogWrite(BLUE_LED_PIN, 255);

    delay(20);

    analogWrite(RED_LED_PIN, 20);
    analogWrite(BLUE_LED_PIN, 255);

    delay(20);
    analogWrite(RED_LED_PIN, 30);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 40);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 50);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 60);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 70);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 80);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 90);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 100);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 125);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 150);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 175);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 200);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 255);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);

    analogWrite(RED_LED_PIN, 200);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 175);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 150);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 125);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 100);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 90);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 80);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 70);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 60);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 50);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 40);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 30);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 20);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);
    analogWrite(RED_LED_PIN, 10);
    analogWrite(BLUE_LED_PIN, 255);
    delay(20);

    analogWrite(RED_LED_PIN, 10);
    analogWrite(BLUE_LED_PIN, 200);
    delay(20);
    analogWrite(RED_LED_PIN, 10);
    analogWrite(BLUE_LED_PIN, 175);
    delay(20);
    analogWrite(RED_LED_PIN, 10);
    analogWrite(BLUE_LED_PIN, 150);
    delay(20);
    analogWrite(RED_LED_PIN, 10);
    analogWrite(BLUE_LED_PIN, 125);
    delay(20);
    analogWrite(RED_LED_PIN, 10);
    analogWrite(BLUE_LED_PIN, 100);
    delay(20);
    analogWrite(RED_LED_PIN, 10);
    analogWrite(BLUE_LED_PIN, 90);
    delay(20);
    analogWrite(RED_LED_PIN, 10);
    analogWrite(BLUE_LED_PIN, 80);
    delay(20);
    analogWrite(RED_LED_PIN, 10);
    analogWrite(BLUE_LED_PIN, 70);
    delay(20);
    analogWrite(RED_LED_PIN, 10);
    analogWrite(BLUE_LED_PIN, 60);
    delay(20);
    analogWrite(RED_LED_PIN, 10);
    analogWrite(BLUE_LED_PIN, 50);
    delay(20);
    analogWrite(RED_LED_PIN, 10);
    analogWrite(BLUE_LED_PIN, 40);
    delay(20);
    analogWrite(RED_LED_PIN, 10);
    analogWrite(BLUE_LED_PIN, 30);
    delay(20);
    analogWrite(RED_LED_PIN, 10);
    analogWrite(BLUE_LED_PIN, 20);
    delay(20);
    analogWrite(RED_LED_PIN, 10);
    analogWrite(BLUE_LED_PIN, 10);
    delay(20);
}
