#include <vs-rc202.h>

#define INTERVAL 1050

void setup() {
  initLib();                //Initilize vs-rc202 library
  servoEnable(1, 1);        //Enable SV1 PWM
  setLedMode(1,1);          //Set SV1 LEDmode
  setServoMovingTime(1000);   //LED brightness changing time
}

void loop() {
  setLedBrightness(1, 0);
  moveServo();
  delay(INTERVAL);
  
  setLedBrightness(1, 1000);
  moveServo();
  delay(INTERVAL);
}
