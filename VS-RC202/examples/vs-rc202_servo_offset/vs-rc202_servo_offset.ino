#include <vs-rc202.h>

void setup() {
  initLib();                //Initilize vs-rc202 library
  servoEnable(1, 1);        //Enable SV1 PWM
  servoEnable(2, 1);        //Enable SV2 PWM
  servoEnable(3, 1);        //Enable SV3 PWM
  servoEnable(4, 1);        //Enable SV4 PWM

  setServoOffset(1, 100);   //Offset range:-500 to 500
  setServoOffset(2, 500);
  setServoOffset(3, -200);
  setServoOffset(4, -500);
}

void loop() {
}
