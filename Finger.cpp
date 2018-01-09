/*
  Finger.cpp - Library for sending keystrokes based on input from glove.
  Created by Sonia Putzel, Jan 10, 2017.
*/

#include "Arduino.h"

#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"



//#include "Keyboard.h"
#include "Finger.h"


Finger::Finger(int pin, bool isLeftHand, int upperLimit, int lowerLimit, Adafruit_BluefruitLE_SPI * ble)
{ 
  _pin = pin;
  _isLeftHand = isLeftHand;
  _readyForKeyUp = false;
  _readyForKeyDown = true;
  _triggerInterval = 1;
  _lowerLimit = lowerLimit;
  _upperLimit = upperLimit;
  bluetoothle = ble;
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

    while (!Serial);  // required for Flora & Micro
           delay(500);
           Serial.begin(115200);
           Serial.println(F("Adafruit Bluefruit HID Keyboard Example"));
           Serial.println(F("---------------------------------------"));
       delay(2000);

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
    Serial.println("key sent");
    reset(currentPos);
  }
}

void Finger::sendKey(int largestAngle) {
  //Keyboard.print(_alphabet[largestAngle]);
  //Keyboard.print("\n");
  Serial.println("send key triggered");
  bluetoothle->println("send key triggered bluetooth");
}

void Finger::reset(int currentPos) {
  _readyForKeyUp = false;
  _largestAngle = currentPos;
  _smallestAngle = currentPos;
  _readyForKeyDown = true;
}

// A small helper
void Finger::error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

void Finger::begin(){
  bluetoothle->begin(true);
}
