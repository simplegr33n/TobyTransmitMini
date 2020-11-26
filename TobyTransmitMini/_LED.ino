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
    crazyPurpleDelayThing();
}

void lightRedLED()
{
    if (settingLEDBrightness > 0)
    {
        analogWrite(RED_LED_PIN, map(settingLEDBrightness, 0, 10, 0, 255));
        digitalWrite(BLUE_LED_PIN, LOW);
    }
    else
    {
        analogWrite(RED_LED_PIN, 0);
        analogWrite(BLUE_LED_PIN, 0);
    }
}

void lightBlueLED()
{
    if (settingLEDBrightness > 0)
    {
        analogWrite(BLUE_LED_PIN, map(settingLEDBrightness, 0, 10, 130, 255));
        digitalWrite(RED_LED_PIN, LOW);
    }
    else
    {
        analogWrite(RED_LED_PIN, 0);
        analogWrite(BLUE_LED_PIN, 0);
    }
}

void lightPurpleLED()
{
    if (settingLEDBrightness > 0)
    {
        analogWrite(RED_LED_PIN, map(settingLEDBrightness, 0, 10, 75, 225));
        analogWrite(BLUE_LED_PIN, 255);
    }
    else
    {
        analogWrite(RED_LED_PIN, 0);
        analogWrite(BLUE_LED_PIN, 0);
    }
}

void turnOffLED()
{
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
}

void crazyPurpleDelayThing()
{
    analogWrite(RED_LED_PIN, 255);
    analogWrite(BLUE_LED_PIN, 255);
    delay(150);
    analogWrite(RED_LED_PIN, 200);
    analogWrite(BLUE_LED_PIN, 255);
    delay(150);
    analogWrite(RED_LED_PIN, 175);
    analogWrite(BLUE_LED_PIN, 255);
    delay(150);
    analogWrite(RED_LED_PIN, 150);
    analogWrite(BLUE_LED_PIN, 255);
    delay(150);
    analogWrite(RED_LED_PIN, 125);
    analogWrite(BLUE_LED_PIN, 255);
    delay(150);
    analogWrite(RED_LED_PIN, 100);
    analogWrite(BLUE_LED_PIN, 255);
    delay(150);
    analogWrite(RED_LED_PIN, 90);
    analogWrite(BLUE_LED_PIN, 255);
    delay(150);
    analogWrite(RED_LED_PIN, 80);
    analogWrite(BLUE_LED_PIN, 255);
    delay(150);
    analogWrite(RED_LED_PIN, 70);
    analogWrite(BLUE_LED_PIN, 255);
    delay(150);
    analogWrite(RED_LED_PIN, 60);
    analogWrite(BLUE_LED_PIN, 255);
    delay(150);
    analogWrite(RED_LED_PIN, 50);
    analogWrite(BLUE_LED_PIN, 255);
    delay(150);
    analogWrite(RED_LED_PIN, 40);
    analogWrite(BLUE_LED_PIN, 255);
    delay(150);
    analogWrite(RED_LED_PIN, 30);
    analogWrite(BLUE_LED_PIN, 255);
    delay(150);
    analogWrite(RED_LED_PIN, 20);
    analogWrite(BLUE_LED_PIN, 255);
    delay(150);
    analogWrite(RED_LED_PIN, 10);
    analogWrite(BLUE_LED_PIN, 255);
    delay(500);
}
