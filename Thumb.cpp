/*
  Thumb.cpp - Library for sending keystrokes based on input from glove.
  Created by Sonia Putzel, Jan 10, 2017.
*/

#include <stdio.h>

#include "Arduino.h"

#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "Thumb.h"

extern void testThumbstroke(Thumb currentThumb);

Thumb::Thumb()
{
}

Thumb::Thumb(int pin, bool isLeftHand, int upperLimit, int lowerLimit, Adafruit_BluefruitLE_SPI * ble)
{
  _pin = pin;
  _isLeftHand = isLeftHand;
  _readyForKeyUp = false;
  _readyForKeyDown = true;
  _triggerInterval = 1;
  _lowerLimit = lowerLimit;
  _upperLimit = upperLimit;
  _ranSetup = false;
  bluetoothle = ble;
  static char const punctuation[] = { '.' , ',' , '\'', '"' , '\b' , ' ' , '!' , '\t' };
  strcpy( _punctuation, punctuation );
  int currentPosition;
}



void Thumb::onLoop()
{
  // this is if we are writing different characters with each finger
  currentPosition = map(analogRead(_pin), _upperLimit, _lowerLimit, 0, 30);

  setLargestAngle();
  setSmallestAngle();
  if (_readyForKeyDown) {
    checkForKeyDown();
  }
  if (_readyForKeyUp) {
    checkForKeyUp();
  }
}

int Thumb::setLargestAngle()
{
  _largestAngle = (currentPosition >= _largestAngle) ? currentPosition : _largestAngle;
}

int Thumb::setSmallestAngle()
{
  _smallestAngle = (currentPosition <= _smallestAngle) ? currentPosition : _smallestAngle;
}

int Thumb::checkForKeyDown() {
  if (currentPosition >= _smallestAngle + _triggerInterval) {
    _readyForKeyDown = false;
    _largestAngle = currentPosition;
    _readyForKeyUp = true;
  }
}

int Thumb::checkForKeyUp() {
  if (currentPosition <= _largestAngle - _triggerInterval) {
    //sendKey(_largestAngle);
    Serial.print("test thumbstroke");
    testThumbstroke(*this);
  }
}

void Thumb::sendKey() {
  //This line doesn't actually print 'AT+BleKeyboard=' - it tells the firmware in the nRF51 module that
  //the following information should be transmitted as output from a BLE keyboard'
  if (_isLeftHand) {
    _relativePos =  map(_largestAngle, 0, 30, 0, 5);
  }
  else {
    _relativePos =  map(_largestAngle, 0, 30, 0, 5) + 4;
  }
  bluetoothle->print("AT+BleKeyboard=");
  bluetoothle->println(_punctuation[_relativePos]);
  Serial.println(_punctuation[_relativePos]);
  //resetPos();
}

void Thumb::resetPos(bool justFired) {
  _readyForKeyUp = false;
  _readyForKeyDown = true;
  _largestAngle = currentPosition;
  Serial.print("just fired? ");
  Serial.println(justFired);
  if (justFired) {
    _smallestAngle = 0;
  }
  else {
    _smallestAngle = currentPosition;
  }
}

int Thumb::currentLargestAngle() {
  return _largestAngle - _smallestAngle;
}

bool Thumb::isReadyForKeyUp() {
  return _readyForKeyUp;
}


