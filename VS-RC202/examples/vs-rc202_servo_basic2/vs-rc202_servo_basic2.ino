#include <vs-rc202.h>

void setup() {

  initLib();                //Initilize vs-rc202 library
  servoEnable(1, 1);        //Enable SV1 PWM
  servoEnable(2, 1);        //Enable SV2 PWM
  servoEnable(3, 1);        //Enable SV3 PWM
  servoEnable(4, 1);        //Enable SV4 PWM
}

void loop() {

  setServoMovingTime(500);  //Set moving time to the target position
  setServoDeg(1, 0);        //Set SV1 servo target position
  setServoDeg(2, 0);        //Set SV2 servo target position
  setServoDeg(3, 0);        //Set SV3 servo target position
  setServoDeg(4, 0);        //Set SV4 servo target position
  moveServo();              //Start to move servo
  delay(700);
  
  setServoMovingTime(500); 
  setServoDeg(1, -1800);   
  setServoDeg(2, 1800); 
  setServoDeg(3, -1800);    
  setServoDeg(4, 1800);     
  moveServo();          
  delay(700);
  
  setServoMovingTime(1000); 
  setServoDeg(1, 1800);  
  setServoDeg(2, -1800);   
  setServoDeg(3, 1800);   
  setServoDeg(4, -1800);  
  moveServo();   
  delay(1200);
}
