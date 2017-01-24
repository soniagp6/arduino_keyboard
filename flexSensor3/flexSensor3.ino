#include "Keyboard.h"
#include <Finger.h>

bool keyboardOn = true;

Finger finger2(0);

void setup()
{
  pinMode(2, INPUT);
  Keyboard.begin();
}

void loop() {
  delay(100); //just here to slow down the output for easier reading
  if ((digitalRead(2)==HIGH) && (keyboardOn==true)) {
    finger2.onLoop();
  }
  else {
    keyboardOn = false;
    Keyboard.end();
  }
}



