/*
  Finger.cpp - Library for sending keystrokes based on input from glove.
  Created by Sonia Putzel, Jan 10, 2017.
*/

#include <stdio.h>

#include "Arduino.h"

#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "Finger.h"

extern void testKeystroke(Finger currentFinger);

Finger::Finger()
{
}

Finger::Finger(int fingerNumber, int pin, bool isLeftHand, int upperLimit, int lowerLimit, Adafruit_BluefruitLE_SPI * ble)
{
  _fingerNumber = fingerNumber;
  _pin = pin;
  _isLeftHand = isLeftHand;
  _readyForKeyUp = false;
  _readyForKeyDown = true;
  _triggerInterval = 1;
  _lowerLimit = lowerLimit;
  _upperLimit = upperLimit;
  _ranSetup = false;
  bluetoothle = ble;
  static char const alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  strcpy( _alphabet, alphabet );
  int currentPosition;
}



void Finger::onLoop()
{
  // this is if we are writing different characters with each finger
  currentPosition = map(analogRead(_pin), _upperLimit, _lowerLimit, (26/8) * (_fingerNumber - 1), (26/8) * (_fingerNumber));
  // this is if we are writing all the characters on each finger
  //int currentPosition = map(analogRead(_pin), 640, 370, 0, 25);

  setLargestAngle();
  setSmallestAngle();
  if (_readyForKeyDown) {
    checkForKeyDown();
  }
  if (_readyForKeyUp) {
    checkForKeyUp();
  }
}

int Finger::setLargestAngle()
{
  _largestAngle = (currentPosition >= _largestAngle) ? currentPosition : _largestAngle;
}

int Finger::setSmallestAngle()
{
  _smallestAngle = (currentPosition <= _smallestAngle) ? currentPosition : _smallestAngle;
}

int Finger::checkForKeyDown() {
  if (currentPosition >= _smallestAngle + _triggerInterval) {
    _readyForKeyDown = false;
    _largestAngle = currentPosition;
    _readyForKeyUp = true;
  }
}

int Finger::checkForKeyUp() {
  if (currentPosition <= _largestAngle - _triggerInterval) {
    testKeystroke(*this);
    resetPos();
  }
}

void Finger::sendKey(int largestAngle) {
  //This line doesn't actually print 'AT+BleKeyboard=' - it tells the firmware in the nRF51 module that
  //the following information should be transmitted as output from a BLE keyboard
  bluetoothle->print("AT+BleKeyboard=");
  bluetoothle->println(_alphabet[largestAngle - 1]);
  resetPos();
}

void Finger::resetPos() {
  _readyForKeyUp = false;
  _largestAngle = currentPosition;
  _smallestAngle = currentPosition;
  _readyForKeyDown = true;
}

int Finger::currentLargestAngle() {
  return _largestAngle;
}

