#include <vs-rc202.h>

void setup() {

  initLib();                //Initilize vs-rc202 library
  servoEnable(1, 1);        //Enable SV1 PWM
  setServoMovingTime(1000); //Set moving time to the target position
}

void loop() {

  setServoDeg(1, 0);        //Set SV1 servo target position
  moveServo();              //Start to move servo
  delay(1200);
  setServoDeg(1, 1500);
  moveServo();
  delay(1200);
  setServoDeg(1, 0);
  moveServo();
  delay(1200);
  setServoDeg(1, -1500);
  moveServo();
  delay(1200);
}