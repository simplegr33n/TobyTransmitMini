#define JOYSTICK0_X_Pin A0
#define JOYSTICK0_Y_Pin A1
#define JOYSTICK0_SW_Pin 2

#define BIG_RED_BUTTON_Pin 3
#define BIG_YELLOW_BUTTON_Pin 4

#define ENCODER_CLK_Pin 5
#define ENCODER_DT_Pin 6
#define ENCODER_SW_Pin 7

volatile uint8_t ENCODER_PHASE;
volatile uint8_t PREV_ENCODER_PHASE;

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

    // Set up encoder pots and switch
    pinMode(ENCODER_CLK_Pin, INPUT);
    pinMode(ENCODER_DT_Pin, INPUT);
    pinMode(ENCODER_SW_Pin, INPUT);

    // Initialize Encoder interrupts
    cli();
    ENCODER_PHASE = PIND;                      // Get state of Port D
    PCICR |= (1 << PCIE2);                     // Pin Change Interrupt Control Register enabling Port K
    PCMSK2 |= (1 << PCINT21) | (1 << PCINT22); // Enable mask on PCINT21-22 to trigger interrupt on state change
    sei();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Input functions                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Handle Pin Change Interrupt Vector
ISR(PCINT2_vect)
{
    cli();
    PREV_ENCODER_PHASE = ENCODER_PHASE;
    ENCODER_PHASE = PIND; // Get state of Port D

    if (ENCODER_PHASE & 0b01100000)
    {
        if ((PREV_ENCODER_PHASE & 0b01000000) && !(PREV_ENCODER_PHASE & 0b00100000))
        {
            updateEncoderCounters(1);
        }
        else if ((PREV_ENCODER_PHASE & 0b00100000) && !(PREV_ENCODER_PHASE & 0b01000000))
        {
            updateEncoderCounters(-1);
        }
    }
    sei();
}

void updateEncoderCounters(int changeValue)
{
    // // DEBUG
    // Serial.print("encoderCounter");
    // Serial.println(encoderCounter);

    if (SETTING_STATE != 0) // if currently setting
    {
        SettingPosition += changeValue;
        return;
    }
    else if (MENU_STATE != 0) // if currently in menu
    {
        MenuPosition += changeValue;
        return;
    }
    else
    {
        encoderCounter += changeValue; // only change actual encoder counter (a value which is transmitted) if not in menu/setting something
    }
}

void updateInputs()
{
    getJoystick0Values();
    getButtonValues();
}

void getJoystick0Values() // Joystick X value
{
    int xPotValue = analogRead(JOYSTICK0_X_Pin);
    joystick0ValueX = map(xPotValue, 0, 1023, 0, 180); // Joystick X value
    int yPotValue = analogRead(JOYSTICK0_Y_Pin);
    joystick0ValueY = map(yPotValue, 0, 1023, 0, 180); // Joystick Y value
}

void getButtonValues()
{
    bigRedButtonValue = digitalRead(BIG_RED_BUTTON_Pin);       // Big red button value
    bigYellowButtonValue = digitalRead(BIG_YELLOW_BUTTON_Pin); // Big yellow button value

    joystick0ValueSw = 0; // Joystick Switch value
    if (digitalRead(JOYSTICK0_SW_Pin) == 0)
    {
        joystick0ValueSw = 1;
    }

    encoderSwitchValue = 0; // Encoder switch value
    if (digitalRead(ENCODER_SW_Pin) == 0)
    {
        encoderSwitchValue = 1;
    }
}
