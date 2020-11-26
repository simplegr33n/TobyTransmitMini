bool TxOsRunning = false; // TODO: does nothing for now, but could be used to reboot OS in cases of lost NRF cxn, etc.

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Hardware Inputs                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int joystick0ValueX;
int joystick0ValueY;
int joystick0ValueSw;

int bigRedButtonValue;
int bigYellowButtonValue;

int encoderSwitchValue;
volatile int encoderCounter = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// OS vars                                                                                             //
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int MENU_STATE = 0; // 0 = off, 1 = Main Menu, 2 = Vehicle Settings, 3 = Controller Settings, 4 = Datalog,
volatile int MenuPosition;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ///////////////                                                                                     //
// END GLOBAL VARS                                                                                     //
// ///////////////                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
    bootTxOs();
}

void loop()
{
    if (TxOsRunning)
    {
        TxOsLoop();
    }
    else
    {
        bootTxOs();
    }
}
