/*
  Finger.h - Library for sending keystrokes based on input from glove.
  Created by Sonia Putzel, Jan 10, 2017.
*/

#ifndef Finger_h
#define Finger_h

#include "Arduino.h"
#include "Keyboard.h"

#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

class Finger
{
  public:
    Finger(int pin, bool isLeftHand, int upperLimit, int lowerLimit);
    int setLargestAngle(int currentPos);
    int setSmallestAngle(int currentPos);
    int checkForKeyDown(int currentPos);
    int checkForKeyUp(int currentPos);
    void sendKey(int currentPos);
    void reset(int currentPos);
    void onLoop();
    void error();

  private:
    char _alphabet[100];
    int _pin;
    int _largestAngle;
    int _smallestAngle;
    boolean _readyForKeyUp;
  	boolean _readyForKeyDown;
  	int _triggerInterval;
    boolean _isLeftHand;
    int _fingerNumber;
    int _lowerLimit;
    int _upperLimit;
};

#endif