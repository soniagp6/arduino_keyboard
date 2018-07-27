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

#include "FingerController.h"
#include "Finger.h"

Finger::Finger()
{
}

Finger::Finger(int fingerNumber, int pin, bool isLeftHand, int upperLimit, int lowerLimit, Adafruit_BluefruitLE_SPI * ble, FingerController &fc)
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
  //fingerController = &fc;
}



void Finger::onLoop()
{
  Serial.println("finger onloop");
  bluetoothle->print("AT+BleKeyboard=");
  bluetoothle->println("finger");
  // this is if we are writing different characters with each finger
  int currentPosition = map(analogRead(_pin), _upperLimit, _lowerLimit, (26/8) * (_fingerNumber - 1), (26/8) * (_fingerNumber));
  // this is if we are writing all the characters on each finger
  //int currentPosition = map(analogRead(_pin), 640, 370, 0, 25);

  setLargestAngle(currentPosition);
  setSmallestAngle(currentPosition);
  if (_readyForKeyDown) {
    checkForKeyDown(currentPosition);
  }
  if (_readyForKeyUp) {
    checkForKeyUp(currentPosition);
  }
    Serial.println(analogRead(_pin));
}

int Finger::setLargestAngle(int currentPos)
{
  _largestAngle = (currentPos >= _largestAngle) ? currentPos : _largestAngle;
}

int Finger::setSmallestAngle(int currentPos)
{
  _smallestAngle = (currentPos <= _smallestAngle) ? currentPos : _smallestAngle;
}

int Finger::checkForKeyDown(int currentPos) {
  if (currentPos >= _smallestAngle + _triggerInterval) {
    _readyForKeyDown = false;
    _largestAngle = currentPos;
    _readyForKeyUp = true;
  }
}

int Finger::checkForKeyUp(int currentPos) {
  if (currentPos <= _largestAngle - _triggerInterval) {
    sendKey(_largestAngle);
    reset(currentPos);
  }
}

void Finger::sendKey(int largestAngle) {
  //This line doesn't actually print 'AT+BleKeyboard=' - it tells the firmware in the nRF51 module that
  //the following information should be transmitted as output from a BLE keyboard
  Serial.print("finger ");
  Serial.println(_fingerNumber);
  Serial.println(largestAngle);
  bluetoothle->print("AT+BleKeyboard=");
  bluetoothle->println(_alphabet[largestAngle - 1]);
}

void Finger::reset(int currentPos) {
  _readyForKeyUp = false;
  _largestAngle = currentPos;
  _smallestAngle = currentPos;
  _readyForKeyDown = true;
}


