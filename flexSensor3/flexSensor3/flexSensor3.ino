#include <Keyboard.h>
#include <Finger.h>


bool keyboardOn = false;
bool isLeftHand = true;
int numLoops = 0; 

Finger finger1(4, isLeftHand);
Finger finger2(3, isLeftHand);
Finger finger3(2, isLeftHand);
Finger finger4(1, isLeftHand);

void setup()
{
  pinMode(2, INPUT);
  Keyboard.begin();
}

void loop() {
  delay(100); //just here to slow down the output for easier reading

  numLoops += 1;
  if (numLoops == 10) {
    checkOnButton();
    numLoops = 0;
  }
 
  if (keyboardOn==true) {
//    finger1.onLoop();
//    finger2.onLoop();
//    finger3.onLoop();
    finger4.onLoop();
  }
}

void checkOnButton() {
  if (digitalRead(2)==HIGH) {
    if (keyboardOn==false) {
      keyboardOn = true;
    }
    else {
      keyboardOn = false;
    }
  }
}

