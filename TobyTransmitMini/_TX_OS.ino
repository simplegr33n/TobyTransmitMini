/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Input debounce                                                                                      //
/////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned long lastEncoderPress = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ///////////////                                                                                     //
// END GLOBAL VARS                                                                                     //
// ///////////////                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void bootTxOs()
{
    Serial.begin(115200);
    initIndicatorLeds(); // init indicator LEDS
    initOLED();          // init display
    initInputs();        // init transimitter inputs
    initNRF24();         // init nrf24 transceiver

    TxOsRunning = true;
}

void TxOsLoop()
{
    lightPurpleLED();

    sendRadioCom(); // send RF communication via NRF24L01
    updateInputs(); // get updated input states

    if (MENU_STATE != 0)
    {
        MenuHandler();
        return;
    }
    else
    {
        if (encoderSwitchValue == 1 && (millis() - lastEncoderPress > 500))
        {
            lastEncoderPress = millis();
            OpenMenu();
            return;
        }
    }

    updateHomeScreen(); // Update OLED main screen
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Menu functions                                                                                      //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void MenuHandler()
{
    SettingsHandler();

    // Watch for Encoder presses
    if (encoderSwitchValue == 1 && (millis() - lastEncoderPress > 500))
    {
        lastEncoderPress = millis();

        switch (MENU_STATE)
        {
        case 1: // Main Menu
            switch (MenuPosition)
            {
            case 0:
                CloseMenu();
                return;
                break;
            case 1:
                OpenSubmenu(2);
                return;
                break;
            case 2:
                OpenSubmenu(3);
                return;
                break;
            case 3:
                OpenSubmenu(4);
                return;
                break;
            default:
                break;
            }
            break;
        case 2: // Vehicle Settings
            switch (MenuPosition)
            {
            case 0:
                CloseMenu();
                return;
                break;
            default:
                break;
            }
            break;
        case 3: // Controller Settings
            switch (MenuPosition)
            {
            case 0:
                CloseMenu();
                return;
                break;
            case 1: // LED Brightness
                if (SETTING_STATE == 1)
                {
                    SETTING_STATE = 0;
                }
                else
                {
                    SETTING_STATE = 1;
                    SetLEDBrightness();
                }
                return;
                break;
            default:
                break;
            }
            break;
        case 4: // Datalog
            switch (MenuPosition)
            {
            case 0:
                CloseMenu();
                return;
                break;
            default:
                break;
            }
            break;
        default:

            break;
        }
    }

    displayMenu();
}

void OpenMenu()
{
    MENU_STATE = 1;
    MenuPosition = 1;
    displayMenu();
}

void CloseMenu()
{
    MENU_STATE = 0;
}

void OpenSubmenu(int submenuIndex)
{
    MENU_STATE = submenuIndex;
    MenuPosition = 1;
    displayMenu();
}

//
void SettingsHandler()
{
    if (SETTING_STATE == 1)
    {
        switch (MENU_STATE)
        {
        case 2: // Vehicle Settings
            switch (MenuPosition)
            {
            default:
                break;
            }
            break;
        case 3: // Controller Settings
            switch (MenuPosition)
            {
            case 1: // LED Brightness
                SetLEDBrightness();
                break;
            default:
                break;
            }
            break;
        case 4: // Datalog
            switch (MenuPosition)
            {
            default:
                break;
            }
            break;
        default:

            break;
        }
    }
}

void SetLEDBrightness()
{
    int updateInt = settingLEDBrightness + SettingPosition;

    if (updateInt > 10)
    {
        settingLEDBrightness = 10;
    }
    else if (updateInt < 0)
    {
        settingLEDBrightness = 0;
    }
    else
    {
        settingLEDBrightness = updateInt;
    }

    SettingPosition = 0;
}
