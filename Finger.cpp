/*
  Finger.cpp - Library for sending keystrokes based on input from glove.
  Created by Sonia Putzel, Jan 10, 2017.
*/

#include "Arduino.h"
#include "Keyboard.h"
#include "Finger.h"


Finger::Finger(int pin, bool isLeftHand)
{ 
  _pin = pin;
  _isLeftHand = isLeftHand;
  _readyForKeyUp = false;
  _readyForKeyDown = true;
  _triggerInterval = 1;
  static char const alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  if (_isLeftHand) {
    _fingerNumber = _pin + 1;
  }
  else {
    _fingerNumber = _pin + 4;
  }
  strcpy( _alphabet, alphabet );
}

void Finger::onLoop()
{
  // Keyboard.print(analogRead(_pin));
  // Keyboard.print("\n");
  // this is if we are writing different characters with each finger
  //int currentPosition = map(analogRead(_pin), 380, 680, (26/8) * _fingerNumber, (26/8) * _fingerNumber - 4);
  int currentPosition = map(analogRead(_pin), 680, 380, 0, 25);
  setLargestAngle(currentPosition);
  setSmallestAngle(currentPosition);
  if (_readyForKeyDown) {
    checkForKeyDown(currentPosition);
  }
  if (_readyForKeyUp) {
    checkForKeyUp(currentPosition);
  }
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
    sendKey(currentPos);
    reset(currentPos);
  }
}

void Finger::sendKey(int currentPos) {

  Keyboard.print(_alphabet[currentPos]);
  Keyboard.print("\n");
}

void Finger::reset(int currentPos) {
  _readyForKeyUp = false;
  _largestAngle = currentPos;
  _smallestAngle = currentPos;
  _readyForKeyDown = true;
}