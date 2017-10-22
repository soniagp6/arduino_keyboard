#include <Keyboard.h>
#include <Finger.h>


bool keyboardOn = false;
int numLoops = 0;
int ledPin = 10;

//Finger finger0(5, true);
//Finger finger1(4, true, 0, 0);
//Finger finger2(3, true, 650, 350);
//Finger finger3(2, true, 670, 460);
//Finger finger4(1, true, 600, 380);

//Finger finger0(5, false, 0, 0);
Finger finger1(4, false, 490, 150);
Finger finger2(3, false, 650, 350);
Finger finger3(2, false, 600, 320);
Finger finger4(1, false, 680, 410);


void setup()
{
  pinMode(2, INPUT);
  pinMode(ledPin, OUTPUT);
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
      finger2.onLoop();

      //Middle
      //Left hand
      //DEFG
      //Range 670 to 460
      //Right hand 
      //Range 600 to 400
      //RSTU
      finger3.onLoop();
      
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
  if (digitalRead(2)==HIGH) {
    if (keyboardOn==false) {
      keyboardOn = true;
      digitalWrite(ledPin, HIGH); 
    }
    else {
      keyboardOn = false;
      digitalWrite(ledPin, LOW);
    }
  }
}

