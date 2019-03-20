#include <vs-rc202.h>

void setup() {

  //Init robot lib
  initLib();
  delay(10);

  //Set position 0 to SV1-10
  int i;
  for(i=1;i<=10;i++){
    servoEnable(i, 1);        //Enable PWM
    setServoDeg(i, 0);        //Set position 0
  }
  moveServo();                //Move servos
}

void loop() {

}


