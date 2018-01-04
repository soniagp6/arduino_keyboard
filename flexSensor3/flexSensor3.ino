#include <Arduino.h>

// For Bluetooth
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"

#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

#include <Keyboard.h>
#include <Finger.h>


#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"

/* ...hardware SPI, using SCK/MOSI/MISO hardware SPI pins and then user selected CS/IRQ/RST */
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

bool keyboardOn = false;
int ledPin = 12;
int inputPin = 11;
int buttonState = 0;

//Finger finger0(5, true);
Finger finger1(4, true, 0, 0);
Finger finger2(3, true, 650, 350);
Finger finger3(2, true, 670, 460);
Finger finger4(1, true, 600, 380);

//Finger finger0(5, false, 0, 0);
//Finger finger1(4, false, 490, 150);
//Finger finger2(3, false, 650, 350);
//Finger finger3(2, false, 600, 320);
//Finger finger4(1, false, 680, 410);


// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

void setup()
{
  pinMode(inputPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(inputPin, HIGH);
  Keyboard.begin();
  while (!Serial);  // required for Flora & Micro
  delay(500);

  Serial.begin(115200);
  Serial.println(F("Adafruit Bluefruit HID Keyboard Example"));
  Serial.println(F("---------------------------------------"));

  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      error(F("Couldn't factory reset"));
    }
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  /* Change the device name to make it easier to find */
  Serial.println(F("Setting device name to 'Bluefruit Keyboard': "));
  if (! ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=Bluefruit Keyboard" )) ) {
    error(F("Could not set device name?"));
  }

  /* Enable HID Service */
  Serial.println(F("Enable HID Service (including Keyboard): "));
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    if ( !ble.sendCommandCheckOK(F( "AT+BleHIDEn=On" ))) {
      error(F("Could not enable Keyboard"));
    }
  }else
  {
    if (! ble.sendCommandCheckOK(F( "AT+BleKeyboardEn=On"  ))) {
      error(F("Could not enable Keyboard"));
    }
  }

  /* Add or remove service requires a reset */
  Serial.println(F("Performing a SW reset (service changes require a reset): "));
  if (! ble.reset() ) {
    error(F("Couldn't reset??"));
  }

  Serial.println();
  Serial.println(F("Go to your phone's Bluetooth settings to pair your device"));
  Serial.println(F("then open an application that accepts keyboard input"));

  Serial.println();
  Serial.println(F("Enter the character(s) to send:"));
  Serial.println(F("- \\r for Enter"));
  Serial.println(F("- \\n for newline"));
  Serial.println(F("- \\t for tab"));
  Serial.println(F("- \\b for backspace"));

  Serial.println();
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

  Serial.print(F("keyboard > "));

  // Check for user input and echo it back if anything was found
  char keys[BUFSIZE+1];
  getUserInput(keys, BUFSIZE);

  Serial.print("\nSending ");
  Serial.println(keys);

  ble.print("AT+BleKeyboard=");
  ble.println(keys);

  if( ble.waitForOK() )
  {
    Serial.println( F("OK!") );
  }else
  {
    Serial.println( F("FAILED!") );
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

/**************************************************************************/
/*!
    @brief  Checks for user input (via the Serial Monitor)
*/
/**************************************************************************/
void getUserInput(char buffer[], uint8_t maxSize)
{
  memset(buffer, 0, maxSize);
  while( Serial.available() == 0 ) {
    delay(1);
  }

  uint8_t count=0;

  do
  {
    count += Serial.readBytes(buffer+count, maxSize);
    delay(2);
  } while( (count < maxSize) && !(Serial.available() == 0) );
}

