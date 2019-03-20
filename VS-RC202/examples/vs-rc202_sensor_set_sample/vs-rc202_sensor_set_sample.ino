#include <vs-rc202.h>
#include <Arduino.h>

#define GO 0
#define LEFT 1
#define RIGHT 2
#define BACK 3
#define STOP 4
#define LOOK 5

int ir_flag = 0;

int home_position[1][11] = {
                      {800,0,0,0,0,0,0,0,0,0,0},
                    };

int go[6][11] = {
                  {300,0,0,800,0,0,0,0,0,0,0},
                  {300,-600,-600,800,0,0,0,0,0,0,0},
                  {300,-600,-600,0,0,0,0,0,0,0,0},
                  {300,-600,-600,-800,0,0,0,0,0,0,0},
                  {300,600,600,-800,0,0,0,0,0,0,0},
                  {300,600,600,0,0,0,0,0,0,0,0},
                };
                

int left[5][11] = {
                    {300,0,0,-600,0,0,0,0,0,0,0},
                    {300,300,0,-600,0,0,0,0,0,0,0},
                    {500,300,0,600,0,0,0,0,0,0,0},
                    {300,0,0,600,0,0,0,0,0,0,0},
                    {300,0,0,0,0,0,0,0,0,0,0},
                    };


int right[5][11] = {
                    {300,0,0,600,0,0,0,0,0,0,0},
                    {300,0,-300,600,0,0,0,0,0,0,0},
                    {500,0,-300,-600,0,0,0,0,0,0,0},
                    {300,0,0,-600,0,0,0,0,0,0,0},
                    {300,0,0,0,0,0,0,0,0,0,0},
                    };

int back[6][11] = {
                  {300,0,0,-800,0,0,0,0,0,0,0},
                  {300,-600,-600,-800,0,0,0,0,0,0,0},
                  {300,-600,-600,0,0,0,0,0,0,0,0},
                  {300,-600,-600,800,0,0,0,0,0,0,0},
                  {300,600,600,800,0,0,0,0,0,0,0},
                  {300,600,600,0,0,0,0,0,0,0,0},
                };


void selectMotion(){
  
  switch(getMotionNumber()){
    case GO:
      playMotionOnce(go, 6);
      break;
    case LEFT:
      playMotionOnce(left, 5);
      break;
    case RIGHT:
      playMotionOnce(right, 5);
      break;
    case BACK:
      playMotionOnce(back, 6);
      break;
    case STOP:
      stopServo();
      delay(200);
      playMotionOnce(home_position, 1);
      break;
  }
}

void setup() {

  //Init robot lib
  initLib();

  //SV1 - 4 servo mode
  servoEnable(1, 1);        //Enable SV1 PWM
  servoEnable(2, 1);        //Enable SV2 PWM
  servoEnable(3, 1);        //Enable SV3 PWM
  servoEnable(4, 1);        //Enable SV4 PWM

  //SV9 and SV10 LED mode
  servoEnable(9, 1);        //Enable SV9 PWM    
  servoEnable(10, 1);       //Enable SV10 PWM
  setLedMode(9, 1);         //Set SV9 LED mode
  setLedMode(10, 1);        //Set SV10 LED mode

  //Offset
  setServoOffset(1,0);
  setServoOffset(2,0);
  setServoOffset(3,0);
  setServoOffset(4,0);
}

void loop() {
  int sens[5];
  sens[0] = readSens(1);      //Read sensor data from AN1 to AN3
  sens[1] = readSens(2);
  sens[2] = readSens(3);
  sens[3] = (int)getDist();   //Get distance from sonic sensor

  if(sens[0] < 200 || sens[0] > 650){
    setMotionNumber(RIGHT);
    setLedBrightnessDirect(9, 0);
    setLedBrightnessDirect(10, 1000);
  }else if(sens[1] < 250 || sens[1] > 650){
    setMotionNumber(LEFT);
    setLedBrightnessDirect(9, 1000);
    setLedBrightnessDirect(10, 0);
  }else if(sens[3] > 250 && sens[3] < 350){
    setMotionNumber(GO);
    setLedBrightnessDirect(9, 1000);
    setLedBrightnessDirect(10, 1000);
  }else if(sens[3] > 30 && sens[3] < 100){
    setMotionNumber(BACK);
    setLedBrightnessDirect(9, 0);
    setLedBrightnessDirect(10, 0);
  }else if(sens[2]> 900){
    if(ir_flag == 0){
      ir_flag = 1;
      setLedBrightnessDirect(9, 1000);
      setLedBrightnessDirect(10, 1000);
      delay(500);
      setLedBrightnessDirect(9, 0);
      setLedBrightnessDirect(10, 0);
      delay(500);
      setLedBrightnessDirect(9, 1000);
      setLedBrightnessDirect(10, 1000);
      delay(500);
      setLedBrightnessDirect(9, 0);
      setLedBrightnessDirect(10, 0);
      delay(500);
    }
  }else{
    setMotionNumber(STOP);
    setLedBrightnessDirect(9, 0);
    setLedBrightnessDirect(10, 0);
    ir_flag = 0;
  }

  selectMotion();             //Play motion
}
