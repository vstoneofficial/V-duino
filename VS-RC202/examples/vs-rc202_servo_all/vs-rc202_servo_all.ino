#include <vs-rc202.h>

#define M_NUM0 0    //Motion number
#define M_NUM1 1
#define M_NUM2 2
#define M_NUM3 3
#define M_NUM4 4

//************************************************************************
//Motion
//************************************************************************
int motion0[1][11] = {
                  {600,0,0,0,0,0,0,0,0,0,0},
                };
                
int motion1[3][11] = {
                  {600,1000,1000,1000,1000,0,0,0,0,0,0},
                  {1200,-1000,-1000,-1000,-1000,0,0,0,0,0,0},
                  {600,0,0,0,0,0,0,0,0,0,0},
                };
                
int motion2[4][11] = {
                  {600,1000,-1000,1000,-1000,0,0,0,0,0,0},
                  {1200,-1000,1000,-1000,1000,0,0,0,0,0,0},
                  {600,0,0,0,0,0,0,0,0,0,0},
                };

int motion3[5][11] = {
                  {600,1000,0,0,0,0,0,0,0,0,0},
                  {600,1000,1000,0,0,0,0,0,0,0,0},
                  {600,1000,1000,1000,0,0,0,0,0,0,0},
                  {600,1000,1000,1000,1000,0,0,0,0,0,0},
                  {600,0,0,0,0,0,0,0,0,0,0},
                };

int motion4[5][11] = {
                  {600,1000,0,0,0,0,0,0,0,0,0},
                  {600,1000,-1000,0,0,0,0,0,0,0,0},
                  {600,1000,-1000,1000,0,0,0,0,0,0,0},
                  {600,1000,-1000,1000,-1000,0,0,0,0,0,0},
                  {600,0,0,0,0,0,0,0,0,0,0},
                 };

//************************************************************************
//Play motion
//************************************************************************
void selectMotion(){
  switch(getMotionNumber()){              
    case M_NUM0:
      playMotionOnce(motion0, 1);
      break;
    case M_NUM1:
      playMotionOnce(motion1, 3);
      break;
    case M_NUM2:
      playMotionOnce(motion2, 3);
      break;
    case M_NUM3:
      playMotion(motion3, 5);
      break;
    case M_NUM4:
      playMotion(motion4, 5);
      break;
  }
}

//************************************************************************
//Read command
//************************************************************************
void getCommand(){

  if(Serial.available()){
    char a = Serial.read();
    if(a == 'w'){
      setMotionNumber(M_NUM1);
    }else if(a == 'a'){
      setMotionNumber(M_NUM2);
    }else if(a == 'd'){
      setMotionNumber(M_NUM3);
    }else if(a == 's'){
      setMotionNumber(M_NUM4);
    }else if(a == 'x'){
      setMotionNumber(M_NUM0);
    }
    Serial.print(a);
    Serial.println();
    Serial.println("Enter Command w, a, s, d, x");
    Serial.print("$>");
  }
}

void setup() {
  initLib();                //Initilize vs-rc202 library

  setServoLimitL(-1600);    //Set servo limit
  setServoLimitH(1600);

  setServoOffset(1, 0);     //Set SV1-4 offset
  setServoOffset(2, 0);
  setServoOffset(3, 0);
  setServoOffset(4, 0);

  servoEnable(1, 1);        //Enable SV1-4 PWM
  servoEnable(2, 1);        //Enable SV2 PWM
  servoEnable(3, 1);        //Enable SV3 PWM
  servoEnable(4, 1);        //Enable SV4 PWM


  Serial.begin(115200);     //Initialize UART
  Serial.println();
  Serial.println();
  Serial.println("Enter Command w, a, s, d, x");
  Serial.print("$>");
}

void loop() {
  getCommand();             //Read command
  selectMotion();           //Play motion
}
