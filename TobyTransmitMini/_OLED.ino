/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x64 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED pixel width
#define SCREEN_HEIGHT 64 // OLED pixel height

int OLED_RESET = 4;                                                       // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ///////////////                                                                                     //
// END GLOBAL VARS                                                                                     //
// ///////////////                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void initOLED()
{

    Serial.println("OLED Display initiating...");

    // Get display
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    {                                               // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }

    displayBootSequence(); // play OLED init sequence
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// OS Base functions                                                                                   //
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void displayBootSequence(void)
{
    display.clearDisplay();
    // Draw TobySoft 3.0 bootscreen
    display.drawBitmap(
        0,
        0,
        TS5_BMP, 128, 64, 1);

    display.display();
    delay(3000); // show for 3 seconds
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// TxOS  Home Screen functions                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// For Home / Home Graph
void updateHomeScreen()
{
    display.clearDisplay();
    drawSendHeader(); // show send data in header
    displayRxData();  // show rx data in the body
}
void drawSendHeader(void)
{
    // Top bar
    display.fillRect(0, 0, 128, 16, SSD1306_WHITE);

    // L / R text
    display.setTextSize(1.5); // 2:1 pixel scale
    display.setTextColor(SSD1306_BLACK);

    display.setCursor(8, 4); // Start at top-left corner
    display.println('x');
    display.fillRect(16, 1, 20, 12, SSD1306_BLACK);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(18, 4);
    display.println(joystick0ValueX);
    //
    display.setTextColor(SSD1306_BLACK);
    display.setCursor(39, 4);
    display.println('y');
    display.fillRect(47, 1, 20, 12, SSD1306_BLACK);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(49, 4);
    display.println(joystick0ValueY);

    // Robot Mode text
    display.drawRect(96, 1, 31, 14, SSD1306_BLACK);
    //    display.fillRect(51, 1, 20, 12, SSD1306_BLACK);
    display.setTextColor(SSD1306_BLACK);
    //
    display.setCursor(100, 4);
    if (ackData[0] == 0)
    {
        display.fillRect(98, 3, 27, 10, SSD1306_BLACK);
        display.setTextColor(SSD1306_WHITE);
        display.println("FREE");
    }
    else if (ackData[0] == 1)
    {
        display.println("SAFE");
    }
    else if (ackData[0] == 2)
    {
        display.println("AUTO");
    }
    else
    {
        display.println("N/C");
    }
}
void displayRxData(void)
{
    if (ackData[0] != -1)
    {
        drawDistanceBlocks();

        // L / C / R distances text
        display.setTextSize(1.5); // 1.5:1 pixel scale
        display.setTextColor(SSD1306_WHITE);

        display.fillRect(7, 47, 20, 12, SSD1306_BLACK);
        display.setCursor(8, 50);
        display.println(ackData[2]);
        //
        display.fillRect(55, 47, 20, 12, SSD1306_BLACK);
        display.setCursor(56, 50);
        display.println(ackData[1]);
        //
        display.fillRect(104, 47, 20, 12, SSD1306_BLACK);
        display.setCursor(105, 50);
        display.println(ackData[3]);

        display.display();
    }
    else
    {
        // Note Connected text
        display.setTextSize(3.5); // 3:1 pixel scale
        display.setTextColor(SSD1306_WHITE);

        display.setCursor(6, 30);
        display.println("N/C!");

        display.display();
    }
}
void drawDistanceBlocks(void)
{

    const int graphDistanceDivisor = 45; // approx range of values of interest for graph, ie. 0-45cm

    // Get left/center/right height ratios
    float leftHeight = (float)ackData[2] / graphDistanceDivisor;
    if (leftHeight > 1)
    {
        leftHeight = 1;
    }
    float centerHeight = (float)ackData[1] / graphDistanceDivisor;
    if (centerHeight > 1)
    {
        centerHeight = 1;
    }
    float rightHeight = (float)ackData[3] / graphDistanceDivisor;
    if (rightHeight > 1)
    {
        rightHeight = 1;
    }

    // draw L/C/R rects
    display.fillRect(0, 16 + (48 * (leftHeight)), 34, 64, SSD1306_WHITE);    // LEFT (0-34)
    display.fillRect(35, 16 + (48 * (centerHeight)), 58, 64, SSD1306_WHITE); // CENTER (35-(64)-92)
    display.fillRect(94, 16 + (48 * (rightHeight)), 128, 64, SSD1306_WHITE); // RIGHT (94-128)
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// TxOS  Menu functions                                                                                //
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void displayMenu(void)
{
    display.clearDisplay();
    // Draw main menu header
    display.drawBitmap(
        0,
        0,
        mnHeader, 128, 16, 1);

    switch (MENU_STATE)
    {
    case 1: // Main Menu
        display.drawBitmap(
            26,
            1,
            mnHeadingMenu, 69, 14, 1);
        display.drawBitmap(
            0,
            17,
            mnIconArray, 128, 48, 1);

        switch (MenuPosition)
        {
        case 0:
            display.fillRect(96, 1, 31, 14, SSD1306_BLACK);
            display.drawBitmap(
                96,
                1,
                mnIconExitHL, 31, 14, 1);
            break;
        case 1:
            display.fillRect(1, 17, 41, 48, SSD1306_BLACK);
            display.drawLine(4, 63, 39, 63, SSD1306_WHITE);
            display.drawBitmap(
                1,
                17,
                mnIconVehicleHL, 41, 48, 1);
            break;
        case 2:
            display.fillRect(43, 17, 42, 48, SSD1306_BLACK);
            display.drawLine(46, 63, 82, 63, SSD1306_WHITE);
            display.drawBitmap(
                43,
                17,
                mnIconTxConfgHL, 42, 48, 1);
            break;
        case 3:
            display.fillRect(86, 17, 41, 48, SSD1306_BLACK);
            display.drawLine(89, 63, 124, 63, SSD1306_WHITE);
            display.drawBitmap(
                86,
                17,
                mnIconDatalogHL, 41, 48, 1);
            break;
        default:
            if (MenuPosition > 3)
            {
                MenuPosition = 0;
            }
            if (MenuPosition < 0)
            {
                MenuPosition = 3;
            }
            break;
        }
        break;
    case 2: // Vehicle Settings
        display.drawBitmap(
            26,
            1,
            mnHeadingVehicle, 69, 14, 1);
        display.fillRect(0, 17, 128, 48, SSD1306_BLACK);

        switch (MenuPosition)
        {
        case 0:
            display.fillRect(96, 1, 31, 14, SSD1306_BLACK);
            display.drawBitmap(
                96,
                1,
                mnIconExitHL, 31, 14, 1);
            break;
        default:
            if (MenuPosition > 1)
            {
                MenuPosition = 0;
            }
            if (MenuPosition < 0)
            {
                MenuPosition = 1;
            }
            break;
        }
        break;
    case 3: // Controller Settings
        display.drawBitmap(
            26,
            1,
            mnHeadingTxConfg, 69, 14, 1);

        display.fillRect(0, 17, 128, 48, SSD1306_BLACK);

        drawSettingRow("Joystick Options", 0, 18, false);
        drawSettingRow("LED Brightness:", settingLEDBrightness, 30, true);

        switch (MenuPosition)
        {
        case 0:
            display.fillRect(96, 1, 31, 14, SSD1306_BLACK);
            display.drawBitmap(
                96,
                1,
                mnIconExitHL, 31, 14, 1);
            break;
        case 1: // Joystick Options
            drawSettingRowHL("Joystick Options", 0, 18, false);
            break;
        case 2: // LED Brightness option
            drawSettingRowHL("LED Brightness:", settingLEDBrightness, 30, true);
            break;
        default:
            if (MenuPosition > 2)
            {
                MenuPosition = 0;
            }
            if (MenuPosition < 0)
            {
                MenuPosition = 2;
            }
            break;
        }
        break;
    case 4: // Datalog
        display.drawBitmap(
            26,
            1,
            mnHeadingDatalog, 69, 14, 1);

        display.fillRect(0, 17, 128, 48, SSD1306_BLACK);

        switch (MenuPosition)
        {
        case 0:
            display.fillRect(96, 1, 31, 14, SSD1306_BLACK);
            display.drawBitmap(
                96,
                1,
                mnIconExitHL, 31, 14, 1);
            break;
        default:
            break;
        }
        break;
    default:

        break;
    }

    display.display();
}

void drawSettingRow(String settingName, int settingValue, int settingRowStart, bool showSettingValue)
{
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(2, settingRowStart + 1);
    display.println(settingName);
    if (showSettingValue == true)
    {
        display.setCursor(96, settingRowStart + 1);
        display.println(settingValue);
    }
}

void drawSettingRowHL(String settingName, int settingValue, int settingRowStart, bool showSettingValue)
{
    if (SETTING_STATE == 1)
    {
        display.setTextSize(1);
        display.fillRect(1, settingRowStart, 128, 10, SSD1306_WHITE);
        display.setTextColor(SSD1306_BLACK);
        display.setCursor(2, settingRowStart + 1);
        display.println(settingName);
        display.fillRect(95, settingRowStart, 126, 10, SSD1306_BLACK);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(96, settingRowStart + 1);
        display.println(settingValue);
    }
    else
    {
        display.setTextSize(1);
        display.drawRect(1, settingRowStart, 128, 10, SSD1306_WHITE);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(2, settingRowStart + 1);
        display.println(settingName);
        if (showSettingValue == true)
        {
            display.setCursor(96, settingRowStart + 1);
            display.println(settingValue);
        }
    }
}
