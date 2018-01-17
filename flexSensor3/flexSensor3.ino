#include <Arduino.h>
#include <Finger.h>

#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"

bool keyboardOn = false;
int ledPin = 12;
int inputPin = 11;
int buttonState = 0;

/* ...hardware SPI, using SCK/MOSI/MISO hardware SPI pins and then user selected CS/IRQ/RST */
Adafruit_BluefruitLE_SPI ble(8, 7, 4);


//Finger finger0(5, true);
//Finger finger1(4, true, 0, 0, &ble);
//Finger finger2(3, true, 650, 350, &ble);
//Finger finger3(2, true, 670, 460, &ble);
//Finger finger4(1, true, 600, 380, &ble);

//Finger finger0(5, false, 0, 0, &ble);
//Finger finger1(4, false, 490, 150, &ble);
//Finger finger2(3, false, 650, 350, &ble);
Finger finger3(2, false, 600, 320, &ble);
Finger finger4(1, false, 680, 410, &ble);

#define VERBOSE_MODE  false

void setup(void)
{
  pinMode(inputPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(inputPin, HIGH);
//  while (!Serial);  // required for Flora & Micro
//  delay(500);
//
//  Serial.begin(115200);
//  Serial.println(F("Adafruit Bluefruit HID Keyboard Example"));
//  Serial.println(F("---------------------------------------"));

  /* Initialise the module */
//  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    //error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  //Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    //Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      //error(F("Couldn't factory reset"));
    }
  }
  
  /* Disable command echo from Bluefruit */
  ble.echo(false);

  //Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  /* Change the device name to make it easier to find */
  //Serial.println(F("Setting device name to 'Bluefruit Keyboard': "));
  if (! ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=Bluefruit Keyboard" )) ) {
    error(F("Could not set device name?"));
  }

  /* Enable HID Service */
  //Serial.println(F("Enable HID Service (including Keyboard): "));
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    if ( !ble.sendCommandCheckOK(F( "AT+BleHIDEn=On" ))) {
      //error(F("Could not enable Keyboard"));
    }
  }else
  {
    if (! ble.sendCommandCheckOK(F( "AT+BleKeyboardEn=On"  ))) {
      //error(F("Could not enable Keyboard"));
    }
  }

  /* Add or remove service requires a reset */
  //Serial.println(F("Performing a SW reset (service changes require a reset): "));
  if (! ble.reset() ) {
    //error(F("Couldn't reset??"));
  }
}

void loop() {
  delay(100); //just here to slow down the output for easier reading

  checkOnButton();
 
  if (keyboardOn==true) {
      //New sensor
      
      //finger0.onLoop();

      //Pinky
      //Left hand
      //No response
      //Right hand
      //WXYZ
      //Range 540 to 150
      //finger1.onLoop();

      //Ring
      //Left hand
      //Range 650 to 350
      //GHIJ
      //Right hand
      //Range 650 to 350
      //STUVW
      //finger2.onLoop();

      //Middle
      //Left hand
      //DEFG
      //Range 670 to 460
      //Right hand 
      //Range 600 to 400
      //RSTU
      //finger3.onLoop();
      
      //Index
      //Left hand 
      //Range - 600 to 380
      //ABCD
      //Right hand 
      //Range - 680 to 410
      //NOPQ
      finger4.onLoop();
     
      //Thumb
      //finger5.onLoop();  
  }
}

void checkOnButton() {
  buttonState = digitalRead(inputPin);
  if (buttonState == HIGH) {
    digitalWrite(ledPin, LOW);
    keyboardOn = false;
  } else {
    digitalWrite(ledPin, HIGH);
    keyboardOn = true;
  }
}

// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}
