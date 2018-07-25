/*
  FingerController.h - Library for sending keystrokes based on input from glove.
  Created by Sonia Putzel, Jan 10, 2017.
*/

#ifndef FingerController_h
#define FingerController_h

#include "Arduino.h"
#include "Finger.h"

#include <SPI.h>

class FingerController
{
  public:
    FingerController ();
    FingerController(Adafruit_BluefruitLE_SPI * ble);
    void onLoop();
    void onKeyPress();
    void createFingers();

  private:
    Adafruit_BluefruitLE_SPI * bluetoothle;
    Finger finger5;
};

#endif