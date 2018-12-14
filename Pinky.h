/*
  Pinky.h - Library for sending keystrokes based on input from glove.
  Created by Sonia Putzel, Jan 10, 2017.
*/

#ifndef Pinky_h
#define Pinky_h

#include "Arduino.h"

//#include "Keyboard.h"

#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

class Pinky
{
  public:
    Pinky ();
    Pinky(int pin, bool isLeftHand, int upperLimit, int lowerLimit);
    int setLargestAngle();
    int setSmallestAngle();
    int checkForKeyDown();
    int checkForKeyUp();
    bool capOff();
    int currentPosition;
    void onLoop();
    bool isCapOn();

  private:
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
    boolean _capOn;
};

#endif