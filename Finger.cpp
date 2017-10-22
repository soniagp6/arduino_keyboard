/*
  Finger.cpp - Library for sending keystrokes based on input from glove.
  Created by Sonia Putzel, Jan 10, 2017.
*/

#include "Arduino.h"
#include "Keyboard.h"
#include "Finger.h"


Finger::Finger(int pin, bool isLeftHand, int upperLimit, int lowerLimit)
{ 
  _pin = pin;
  _isLeftHand = isLeftHand;
  _readyForKeyUp = false;
  _readyForKeyDown = true;
  _triggerInterval = 1;
  _lowerLimit = lowerLimit;
  _upperLimit = upperLimit;
  static char const alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  if (_isLeftHand) {
    _fingerNumber = _pin - 1;
  }
  else {
    _fingerNumber = _pin + 3;
  }
  strcpy( _alphabet, alphabet );

}

void Finger::onLoop()
{
  // Keyboard.print(analogRead(_pin));
  // Keyboard.print("\n");


  // this is if we are writing different characters with each finger
  int currentPosition = map(analogRead(_pin), _upperLimit, _lowerLimit + 150, (26/8) * _fingerNumber, (26/8) * _fingerNumber + 4);
  // this is if we are writing all the characters on each finger
  //int currentPosition = map(analogRead(_pin), 640, 370, 0, 25);

  // Keyboard.print(_alphabet[currentPosition]);
  // Keyboard.print("\n");
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
    sendKey(_largestAngle);
    reset(currentPos);
  }
}

void Finger::sendKey(int largestAngle) {
  Keyboard.print(_alphabet[largestAngle]);
  Keyboard.print("\n");
}

void Finger::reset(int currentPos) {
  _readyForKeyUp = false;
  _largestAngle = currentPos;
  _smallestAngle = currentPos;
  _readyForKeyDown = true;
}