#include <vs-rc202.h>

int motion[2][SV_NUM+1] = { 
                          {1500,1500,1500,1500,1500,0,0,0,0,0,0},
                          {1500,-1500,-1500,-1500,-1500,0,0,0,0,0,0}
                      };

void setup() {
  initLib();                 //Initilize vs-rc202 library
  servoEnable(1, 1);         //Enable SV1 PWM
  servoEnable(2, 1);
  servoEnable(3, 1);
  servoEnable(4, 1);
  servoEnable(10, 1);
  setLedMode(10,1);                 //Set SV10 LEDmode
  setLedBrightnessDirect(10, 1000); //Set//Set LED10 brightness 1000 directly LED10 brightness 1000 directly
}

void loop() {
  playMotionOnce(motion, 2);
  delay(20);
}
