/*
  Finger.h - Library for sending keystrokes based on input from glove.
  Created by Sonia Putzel, Jan 10, 2017.
*/

#ifndef Finger_h
#define Finger_h

#include "Arduino.h"
#include "Keyboard.h"

class Finger
{
  public:
    Finger(int pin);
    int setLargestAngle(int currentPos);
    int setSmallestAngle(int currentPos);
    int checkForKeyDown(int currentPos);
    int checkForKeyUp(int currentPos);
    void sendKey(int currentPos);
    void reset(int currentPos);
    void onLoop();

  private:
    char _alphabet[100];
    int _pin;
    int _largestAngle;
    int _smallestAngle;
    boolean _readyForKeyUp;
  	boolean _readyForKeyDown;
  	int _triggerInterval;
};

#endif