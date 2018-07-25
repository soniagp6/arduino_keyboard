/*
  FingerController.cpp - Library for managing Fingers on Glove.
  Created by Sonia Putzel, Jan 10, 2017.
*/

#include "Arduino.h"

#include "FingerController.h"

#include <SPI.h>

#include "Finger.h"


FingerController::FingerController()
{
}

FingerController::FingerController(Adafruit_BluefruitLE_SPI * ble)
{
  bluetoothle = ble;
}

void FingerController::createFingers()
{
  Serial.println("Create Fingers");
  //Left Thumb
  Finger finger5(5, 0, true, 300, 230, bluetoothle, *this);
}

void FingerController::onLoop()
{
  bluetoothle->print("AT+BleKeyboard=");
  bluetoothle->println("fingerController BT");
  //Left Thumb
  //finger5.onLoop();
}

void FingerController::onKeyPress() {
  Serial.println("onKeyPress");
}
