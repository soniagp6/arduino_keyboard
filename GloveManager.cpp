/*
  Thumb.cpp - Library for sending keystrokes based on input from glove.
  Created by Sonia Putzel, Jan 10, 2017.
*/

#include "Arduino.h"

#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"


#include "GloveManager.h"


GloveManager::GloveManager(Finger * fingerArray)
{
  finArray = fingerArray;
}



void GloveManager::onLoop()
{

}


