/*
  Thumb.h - Library for sending keystrokes based on input from glove.
  Created by Sonia Putzel, Jan 10, 2017.
*/

#ifndef Thumb_h
#define Thumb_h

#include "Arduino.h"

//#include "Keyboard.h"

#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

class Thumb
{
  public:
    Thumb ();
    Thumb(int pin, bool isLeftHand, int upperLimit, int lowerLimit, Adafruit_BluefruitLE_SPI * ble);
    int setLargestAngle();
    int setSmallestAngle();
    int checkForKeyDown();
    int checkForKeyUp();
    int currentPosition;
    void sendKey(int largestAngle);
    void resetPos();
    void onLoop();
    int currentLargestAngle();

  private:
    char _punctuation[100];
    int _pin;
    int _largestAngle;
    int _smallestAngle;
    boolean _readyForKeyUp;
  	boolean _readyForKeyDown;
  	int _triggerInterval;
    boolean _isLeftHand;
    boolean _ranSetup;
    int _lowerLimit;
    int _upperLimit;
    int _relativePos;
    void error(const __FlashStringHelper*err);
    Adafruit_BluefruitLE_SPI * bluetoothle;
};

#endif