#include <vs-rc202.h>

#define STEP 100
#define SPEED 100

int POS_SV1 = 0;
int POS_SV2 = 0;
int POS_SV3 = 0;
int POS_SV4 = 0;

char readCommand(){
  if(Serial.available()){
    char command = Serial.read();
    return command;
  }
}

void moveArm(char command){

  switch(command){
    case 'a':
      POS_SV1 += STEP;
      setServoDeg(1, POS_SV1);
      break;
    case 's':
      POS_SV1 -= STEP;
      setServoDeg(1, POS_SV1);
      break;
    case 'd':
      POS_SV2 += STEP;
      setServoDeg(2, POS_SV2);
      break;
    case 'f':
      POS_SV2 -= STEP;
      setServoDeg(2, POS_SV2);
      break;
    case 'g':
      POS_SV3 += STEP;
      setServoDeg(3, POS_SV3);
      break;
    case 'h':
      POS_SV3 -= STEP;
      setServoDeg(3, POS_SV3);
      break;
    case 'j':
      POS_SV4 += STEP;
      setServoDeg(4, POS_SV4);
      break;
    case 'k':
      POS_SV4 -= STEP;
      setServoDeg(4, POS_SV4);
      break;
  }
  moveServo();
}

void setup() {

  initLib();                //Initilize vs-rc202 library
  servoEnable(1, 1);        //Enable SV1 PWM
  servoEnable(2, 1);        //Enable SV1 PWM
  servoEnable(3, 1);        //Enable SV1 PWM
  servoEnable(4, 1);        //Enable SV1 PWM
  setServoMovingTime(SPEED); //Set moving time to the target position

  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println("==================================================");
  Serial.println("Start");
  Serial.println("==================================================");
}

void loop() {

  char cmd = readCommand();
  moveArm(cmd);
}
