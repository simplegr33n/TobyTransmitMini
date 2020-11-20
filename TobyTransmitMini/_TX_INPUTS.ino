#define JOYSTICK0_X_Pin A0
#define JOYSTICK0_Y_Pin A1
#define JOYSTICK0_SW_Pin 2

#define BIG_RED_BUTTON_Pin 3
#define BIG_YELLOW_BUTTON_Pin 4

#define ENCODER_CLK_Pin 5
#define ENCODER_DT_Pin 6
#define ENCODER_SW_Pin 7

int currentStateCLK;
int lastStateCLK;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ///////////////                                                                                     //
// END GLOBAL VARS                                                                                     //
// ///////////////                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void initInputs()
{
    // Set up pin for joystick switch function
    pinMode(JOYSTICK0_SW_Pin, INPUT);
    digitalWrite(JOYSTICK0_SW_Pin, HIGH);

    // Set up button pins
    pinMode(BIG_RED_BUTTON_Pin, INPUT);
    pinMode(BIG_YELLOW_BUTTON_Pin, INPUT);

    // Set up encoder pins
    pinMode(ENCODER_CLK_Pin, INPUT);
    pinMode(ENCODER_DT_Pin, INPUT);
    pinMode(ENCODER_SW_Pin, INPUT_PULLUP);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Input functions                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void updateInputs()
{
    getJoystick0Values();
    getButtonValues();
    getEncoderValues();
}

void getJoystick0Values() // Joystick X value
{
    int xPotValue = analogRead(JOYSTICK0_X_Pin);
    joystick0ValueX = map(xPotValue, 0, 1023, 0, 180); // Joystick X value
    int yPotValue = analogRead(JOYSTICK0_Y_Pin);
    joystick0ValueY = map(yPotValue, 0, 1023, 0, 180); // Joystick Y value
    joystick0ValueSw = 0;                              // Joystick Switch value
    if (digitalRead(JOYSTICK0_SW_Pin) == 0)
    {
        joystick0ValueSw = 1;
    }
}

void getButtonValues()
{
    bigRedButtonValue = digitalRead(BIG_RED_BUTTON_Pin);       // Big red button value
    bigYellowButtonValue = digitalRead(BIG_YELLOW_BUTTON_Pin); // Big yellow button value
}

void getEncoderValues()
{
    getEncoderRotaryValues();
    encoderSwitchValue = digitalRead(ENCODER_SW_Pin); // Encoder switch value

    // DEBUG
    Serial.print("ENCODER! Direction: ");
    Serial.println(rotaryDirection);
    Serial.print(" | Counter: ");
    Serial.println(rotaryCounterValue);
    Serial.print(" | Switch: ");
    Serial.println(encoderSwitchValue);
    if (rotaryDirection > 0)
    {
        lightRedLED();
    }
    else
    {
        lightBlueLED();
    }
}

void getEncoderRotaryValues()
{
    // Read the current state of CLK
    currentStateCLK = digitalRead(ENCODER_CLK_Pin);

    // If last and current state of CLK are different, then pulse occurred
    // React to only 1 state change to avoid double count
    if (currentStateCLK != lastStateCLK && currentStateCLK == 1)
    {

        // If the DT state is different than the CLK state then
        // the encoder is rotating CCW so decrement
        if (digitalRead(ENCODER_DT_Pin) != currentStateCLK)
        {
            rotaryCounterValue--;
            rotaryDirection = -1;
        }
        else
        {
            // Encoder is rotating CW so increment
            rotaryCounterValue++;
            rotaryDirection = 1;
        }
    }

    // Remember last CLK state
    lastStateCLK = currentStateCLK;
}
