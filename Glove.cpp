/*
  Glove.cpp - Library for sending keystrokes based on input from glove.
  Created by Sonia Putzel, Jan 10, 2017.
*/

#include "Arduino.h"

#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

//#include "BluefruitConfig.h"

#include "Glove.h"
#include "Finger.h"
#include "Thumb.h"

using namespace std;

Glove::Glove()
{

    _keyboardOn = false;
    _ledPin = 12;
    _inputPin = 11;
    _buttonState = 0;

    


    pinMode(_inputPin, INPUT);
    pinMode(_ledPin, OUTPUT);
    digitalWrite(_inputPin, HIGH);
//
//    if ( !ble.begin(VERBOSE_MODE) )
//    {
//        error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
//    }
//    Serial.println( F("OK!") );
//
//    if ( FACTORYRESET_ENABLE )
//    {
//    /* Perform a factory reset to make sure everything is in a known state */
//    Serial.println(F("Performing a factory reset: "));
//    if ( ! ble.factoryReset() ){
//        error(F("Couldn't factory reset"));
//    }
//    }
//
//    /* Disable command echo from Bluefruit */
//    ble.echo(false);
//
//    //Serial.println("Requesting Bluefruit info:");
//    /* Print Bluefruit information */
//    ble.info();
//
//    /* Change the device name to make it easier to find */
//    //Serial.println(F("Setting device name to 'Bluefruit Keyboard': "));
//    if (! ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=Bluefruit Keyboard" )) ) {
//        error(F("Could not set device name?"));
//    }
//
//    /* Enable HID Service */
//    Serial.println(F("Enable HID Service (including Keyboard): "));
//    if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
//    {
//    if ( !ble.sendCommandCheckOK(F( "AT+BleHIDEn=On" ))) {
//        error(F("Could not enable Keyboard"));
//    }
//    }else
//    {
//    if (! ble.sendCommandCheckOK(F( "AT+BleKeyboardEn=On"  ))) {
//        error(F("Could not enable Keyboard"));
//    }
//    }
//
//    /* Add or remove service requires a reset */
//    Serial.println(F("Performing a SW reset (service changes require a reset): "));
//    if (! ble.reset() ) {
//        error(F("Couldn't reset??"));
//    }
//
//    finger1 = new Finger(1, 4, true, 490, 450, &ble);
//    finger2 = new Finger(2, 3, true, 500, 450, &ble);

    //    //Left Thumb
    //        Thumb finger5(5, 0, true, 300, 230, &ble);
    //        //Left Index
    //        Finger finger4(4, 1, true, 610, 520, &ble);
    //        //Left Middle
    //        Finger finger3(3, 2, true, 630, 530, &ble);
    //        //Left Ring
    //        Finger finger2(2, 3, true, 500, 450, &ble);
            //Left Pinky
            //Finger finger1(1, 4, true, 490, 450, &ble);

          //Finger finger0(4, false, 0, 0, &ble);
          //Finger finger1(3, false, 490, 150, &ble);
          //Finger finger2(2, false, 650, 350, &ble);
          //Finger finger3(1, false, 600, 320, &ble);
          //Finger finger4(0, false, 680, 410, &ble);

}

void Glove::onLoop()
{
    //just here to slow down the output for easier reading

    //checkOnButton();

    //if (_keyboardOn==true) {

        //Left Pinky
        //finger1->onLoop();

        //Left Ring
        //finger2->onLoop();

        //Left Middle
        //finger3.onLoop();

        //Left Index
        //finger4.onLoop();

        //Left Thumb
        //finger5.onLoop();
    //}
}

void Glove::createFingers()
{



}

void Glove::checkOnButton() {
  _buttonState = digitalRead(_inputPin);
  if (_buttonState == HIGH) {
    digitalWrite(_ledPin, LOW);
    _keyboardOn = false;
  } else {
    digitalWrite(_ledPin, HIGH);
    _keyboardOn = true;
  }
}

// Test global function
void Glove::testFunc() {
  Serial.println("testing global funciton");
}


// A small helper
void Glove::error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}
