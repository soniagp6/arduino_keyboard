#include <Arduino.h>
#include <Finger.h>
#include <Thumb.h>

#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"


bool keyboardOn = false;
int ledPin = 13;
int inputPin = 11;
int buttonState = 0;
bool isLeftHand = true;

/* ...hardware SPI, using SCK/MOSI/MISO hardware SPI pins and then user selected CS/IRQ/RST */
Adafruit_BluefruitLE_SPI ble(8, 7, 4);

// Left hand
//Left Pinky
Finger finger0(0, 4, true, 380, 300, &ble);
//Left Ring
Finger finger1(1, 3, true, 530, 400, &ble);
//Left Middle
Finger finger2(2, 2, true, 680, 585, &ble);
//Left Index
Finger finger3(3, 1, true, 660, 555, &ble);

//Left Thumb
Thumb thumb1(0, true, 443, 520, &ble);

// Right hand
//Right Index
Finger finger4(4, 3, false, 625, 535, &ble);
//Right Middle
Finger finger5(5, 2, false, 590, 460, &ble);
//Right Ring
Finger finger6(6, 1, false, 595, 470, &ble);
//Right Pinky
Finger finger7(7, 0, false, 610, 520, &ble);

//Right Thumb
Thumb thumb2(4, false, 369, 315, &ble);



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
//
//  /* Initialise the module */
//  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    //error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  //Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
//  Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
//      error(F("Couldn't factory reset"));
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
    //error(F("Could not set device name?"));
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

    if (isLeftHand) {
      //Left Pinky
      finger0.onLoop();

//      //Left Ring
      finger1.onLoop();
//
//      //Left Middle
      finger2.onLoop();
//
//      //Left Index
      finger3.onLoop();
//
//      //Left Thumb
      thumb1.onLoop();
    }
    else {
      //Right Index
      finger4.onLoop();

      //Right Middle
      finger5.onLoop();

      //Right Ring
      finger6.onLoop();

      //Right Pinky
      //finger7.onLoop();

      //Right Thumb
      thumb2.onLoop();
    }
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

// Finger checks to see if the distance it has traveled is greater than another
// finger's distance.
void testKeystroke(Finger currentFinger) {
  int fingerDist = currentFinger.currentLargestAngle();
  //currentFinger.sendKey(fingerDist);
  // If distance traveled is greated than other fingers' distance

  if (isLeftHand) {
    if (fingerDist >= finger0.currentLargestAngle() && fingerDist >= finger1.currentLargestAngle() && fingerDist >= finger2.currentLargestAngle() && fingerDist >= finger3.currentLargestAngle() && fingerDist >= thumb1.currentLargestAngle()) {
      currentFinger.sendKey(fingerDist);
      finger0.resetPos();
      finger1.resetPos();
      finger2.resetPos();
      finger3.resetPos();
      thumb1.resetPos();
    }
  }
  else {
    if (fingerDist >= finger4.currentLargestAngle() && fingerDist >= finger5.currentLargestAngle() && fingerDist >= finger6.currentLargestAngle() && fingerDist >= finger7.currentLargestAngle() && fingerDist >= thumb2.currentLargestAngle()) {
      currentFinger.sendKey(fingerDist);
      finger4.resetPos();
      finger5.resetPos();
      finger6.resetPos();
      finger7.resetPos();
      thumb2.resetPos();
    }
  }
  // Tell Finger to send keystroke
  // Reset all fingers

  // If another finger has traveled a greater distance
  // Do nothing
}

// Finger checks to see if the distance it has traveled is greater than another
// finger's distance.
void testThumbstroke(Thumb currentThumb) {
  int fingerDist = currentThumb.currentLargestAngle();
  //currentFinger.sendKey(fingerDist);
  // If distance traveled is greated than other fingers' distance

  if (isLeftHand) {
    if (fingerDist >= finger0.currentLargestAngle() && fingerDist >= finger1.currentLargestAngle() && fingerDist >= finger2.currentLargestAngle() && fingerDist >= finger3.currentLargestAngle() && fingerDist >= thumb1.currentLargestAngle()) {
      currentThumb.sendKey(fingerDist);
      finger0.resetPos();
      finger1.resetPos();
      finger2.resetPos();
      finger3.resetPos();
      thumb1.resetPos();
    }
  }
  else {
    if (fingerDist >= finger4.currentLargestAngle() && fingerDist >= finger5.currentLargestAngle() && fingerDist >= finger6.currentLargestAngle() && fingerDist >= finger7.currentLargestAngle()) {
      currentThumb.sendKey(fingerDist);
      finger4.resetPos();
      finger5.resetPos();
      finger6.resetPos();
      finger7.resetPos();
      thumb2.resetPos();
    }
  }
  // Tell Finger to send keystroke
  // Reset all fingers

  // If another finger has traveled a greater distance
  // Do nothing
}





// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}