/*
  Glove.h - Library for controlling keystrokes.
  Created by Sonia Putzel, Jan 10, 2017.
*/

#ifndef Glove_h
#define Glove_h

#include "Arduino.h"

#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include <Finger.h>
#include <Thumb.h>

class Glove
{
  public:
    Glove();
    void onLoop();
    void testFunc();
  private:
    void error(const __FlashStringHelper*err);
    void checkOnButton();
    void createFingers();
    int _buttonState;
    bool _keyboardOn;
    int _ledPin;
    int _inputPin;
    const bool FACTORYRESET_ENABLE = 0;
    const char MINIMUM_FIRMWARE_VERSION = "0.6.6";
    const bool VERBOSE_MODE = false;
    Finger * finger1;
    Finger * finger2;
};

#endif