#include <vs-rc202.h>

void setup() {
  initLib();
  servoEnable(1,1);      //Enable PWM
}

void loop() {

  int sv_limit = 1800;               //Servo range limit 1800
  int sv_time = sv_limit/2;          //Moving time 900
  int sv_delay = sv_time + 100;      //Wait 1000
  setServoLimitL(-sv_limit);
  setServoLimitH(sv_limit);
  setServoMovingTime(sv_time);
  setServoDeg(1, 0);     
  moveServo();      
  delay(sv_delay);
  setServoDeg(1, 1800);
  moveServo();
  delay(sv_delay);
  setServoDeg(1, 0);
  moveServo();
  delay(sv_delay);
  setServoDeg(1, -1800);
  moveServo();
  delay(sv_delay);
  setServoDeg(1, 0);
  moveServo();
  delay(sv_delay);

  sv_limit = 800;                   //Servo range limit 800
  sv_time = sv_limit/2;             //Moving time 400
  sv_delay = sv_time + 100;         //Wait 500
  setServoLimitL(-sv_limit);
  setServoLimitH(sv_limit);
  setServoMovingTime(sv_time);
  setServoDeg(1, 0);     
  moveServo();      
  delay(sv_delay);
  setServoDeg(1, 1800);
  moveServo();
  delay(sv_delay);
  setServoDeg(1, 0);
  moveServo();
  delay(sv_delay);
  setServoDeg(1, -1800);
  moveServo();
  delay(sv_delay);
  setServoDeg(1, 0);
  moveServo();
  delay(sv_delay);
}
