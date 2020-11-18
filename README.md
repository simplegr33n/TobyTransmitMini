# Toby Transmit Mini

Arduino Nano based RF controller.

## COMPONENTS

// Modules

- Arduino Nano microcontroller

- NRF24L01 RF module

- USB Charging circuit

- SSD1306 OLED screen

- 3-Color indicator LED

// Inputs

- On/Off switch

- XY+Switch Joystick

- Rotary Encoder with Momentary Switch

- Momentary Button

- Switch button

## Nano Pinout

| Pin                | _module_         | _module pin_     | _notes_                                                                                                                                              |
| ------------------ | ---------------- | ---------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------- |
| **_A0_**           | Joystick         | _X_              | X and Y may be swapped based on actual hardware config                                                                                               |
| **_A1_**           | Joystick         | _Y_              |
| **_A2_**           |                  |                  |
| **_A3_**           |                  |                  |
| **_A4_** - _SDA_   | SSD1306 OLED     | _SDA_            |
| **_A5_** - _SCL_   | SSD1306 OLED     | _SCL_            |
| **_A6_**           |                  |                  | \* Exclusively analog pin                                                                                                                            |
| **_A7_**           |                  |                  | \* Exclusively analog pin                                                                                                                            |
| **_D0_** - _RX0_   | ---USB-COM---    | ---USB-COM---    | Transmitter needs to be able to connect with PC to update firmware, etc. therefore leave RX0 / TX1 free                                              |
| **_D1_** - _TX1_   | ---USB-COM---    | ---USB-COM---    |
| **_D2_**           | Joystick         | _Sw_             |
| **_D3_**           | Momentary Button | _Out_            |
| **_D4_**           | Toggle Button    | _Out_            |
| **_D5_**           | Rotary Encoder   | _CLK (Output A)_ |
| **_D6_**           | Rotary Encoder   | _DT (Output B)_  |
| **_D7_**           | Rotary Encoder   | _Sw_             |
| **_D8_**           | 3-Color LED      | _RED_            |
| **_D9_**           | 3-Color LED      | _BLUE_           |
| **_D10_** _SS_     |                  |                  |
| **_D11_** - _MOSI_ | NRF24L01         | _MOSI_           | NRF24L01 requires a clean **3v** power supply to function well; a buck convertor off the battery may be required if the Arduino's 3v doesn't suffice |
| **_D12_** - _MISO_ | NRF24L01         | _MISO_           |
| **_D13_** - _SCK_  | NRF24L01         | _SCK_            |
