#include <vs-rc202.h>
#include <Wire.h>

void moveServo(int motion[SV_NUM+1]){
  
  unsigned char byte_motion[2*(SV_NUM+1)];
  int i;
  
  for(i=0;i<SV_NUM+1;i++){
    byte_motion[i*2] = motion[i] >> 8;
    byte_motion[i*2+1] = motion[i];
  }
  
  Wire.beginTransmission(DEV_ADDR);
  Wire.write(SV_MV_TIME);   
  for(i=0;i<2*(SV_NUM+1);i++){
    Wire.write(byte_motion[i]);
  }
  Wire.write(1);            //Set SV_START 0x01
  Wire.endTransmission();
}

int motion1[SV_NUM+1] = {1500,1500,1500,1500,1500,0,0,0,0,0,0};
int motion2[SV_NUM+1] = {1500,-1500,-1500,-1500,-1500,0,0,0,0,0,0};

void setup(){

  initLib();
  int i;
  for(i=1;i<SV_NUM+1;i++){    //Enable all servo
    servoEnable(i, 1);
  }
}

void loop(){
  moveServo(motion1);
  delay(1550);
  moveServo(motion2);
  delay(1550);
}



