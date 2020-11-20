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
    lightRedLED();

    delay(500);

    lightBlueLED();

    delay(500);

    lightRedLED();

    delay(500);

    turnOffLEDs();
}

void lightRedLED()
{
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, LOW);
}

void lightBlueLED()
{
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, HIGH);
}

void turnOffLEDs()
{
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
}