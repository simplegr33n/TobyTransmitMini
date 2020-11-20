#define JOYSTICK0_X_Pin A0
#define JOYSTICK0_Y_Pin A1
#define JOYSTICK0_SW_Pin 2

#define BIG_RED_BUTTON_Pin 3
#define BIG_YELLOW_BUTTON_Pin 4

#define ENCODER_CLK_Pin 5
#define ENCODER_DT_Pin 6
#define ENCODER_SW_Pin 7

volatile uint8_t prevEncoderPhase;
volatile uint8_t encoderPhase;

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

    // Set up encoder switch
    pinMode(ENCODER_SW_Pin, INPUT);

    // Initialize Encoder innterupts
    cli();
    DDRD = 0b00000000; // Set all bits in Port D Data Direction Register to input
    encoderPhase = PIND;
    PCICR |= (1 << PCIE2);                     // Pin Change Interrupt Control Register enabling Port K
    PCMSK2 |= (1 << PCINT21) | (1 << PCINT22); // Enable mask on PCINT21-22 to trigger interrupt on state change
    sei();
}

// Handle pin change interrupt request 2.
ISR(PCINT2_vect)
{
    prevEncoderPhase = encoderPhase;
    encoderPhase = PIND; // get state of Port D with PIND

    if (prevEncoderPhase == 207 && encoderPhase == 239) // NOTE: More precise encoder reading is possible
    {                                                   // this simply accurately grabs each notch up or down
        encoderCounter += 1;                            // assuming a reasonable turn speed of the encoder
    }
    else if (prevEncoderPhase == 175 && encoderPhase == 239)
    {
        encoderCounter -= 1;
    }

    // // DEBUG
    // Serial.print("PREV: ");
    // Serial.print(prevEncoderPhase);
    // Serial.print(", CUR: ");
    // Serial.println(encoderPhase);
    // Serial.print("COUNTER: ");
    // Serial.print(encoderCounter);
    // Serial.print("sw:");
    // Serial.print(digitalRead(ENCODER_SW_Pin));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Input functions                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

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
