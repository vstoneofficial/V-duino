#include <Wire.h>
#include <vs-rc202.h>
#include <Arduino.h>

int read_count = 0;
unsigned char readBuff[127];
short servoTPOS[SV_NUM];    //servo target position

int current_motion_number = -1;
int pre_current_motion_number = -1;
int motion_status = 0;
int led_status = 0;

void initLib(){

    //Init sonic SENS_1or pin
    pinMode( TRIG, OUTPUT );
    pinMode( ECHO, INPUT );
    delay(10);

    //Init I2C
    Wire.setClock(WIRE_CLK);
    Wire.begin(); 
    delay(10);
    
    //Init servo limit degree
    setServoLimitL(-1800);
    setServoLimitH(1800);

	//Init servo
	int i;
	for(i=0;i<SV_NUM;i++){
		servoEnable(i+1, 0);
		setServoOffset(i+1,0);
		setServoDeg(i+1,0);
		setLedMode(i+1, 0);
		setLedBrightnessDirect(i+1,0);
	}

    //Init moving time
    setServoMovingTime(1000);
}

//Sonic SENS_1or
float getDist(){
  digitalWrite(TRIG, LOW);
  delayMicroseconds(1);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(11);
  digitalWrite(TRIG, LOW);
  int duration = pulseIn(ECHO,HIGH,100000);
  if (duration>0) {
      float distance = duration/2;
      distance = distance*340*100/100000; //Unit(CM)
      return distance;
    }else{
      return 0;
    }
}

void setMotionNumber(int a){
  current_motion_number = a;

   if(pre_current_motion_number != current_motion_number){
    resetMotionStatus();
    pre_current_motion_number = current_motion_number;
  }
}

int getMotionNumber(){
  return current_motion_number;
}

void resetMotionStatus(){
  motion_status = 0;
}

void playMotion(int motion[][SV_NUM+1], int array_length){

  if(servoAvailable()){

    setMotion(motion[motion_status]);
    
    if(motion_status>=array_length-1){
      resetMotionStatus();
    }else{
      motion_status++;        //move to next status
    }
  }
}

void playMotion(int motion[][SV_NUM+1], int array_length, int sv_num){

  if(servoAvailable()){

    setMotion(motion[motion_status], sv_num);
    
    if(motion_status>=array_length-1){
      resetMotionStatus();
    }else{
      motion_status++;        //move to next status
    }
  }
}


void playMotionOnce(int motion[][SV_NUM+1], int array_length){

  if(servoAvailable()){

    setMotion(motion[motion_status]);
    
    if(motion_status>=array_length-1){
      resetMotionStatus();
      setMotionNumber(999);
      return;
    }else{
      motion_status++;        //move to next status
    }
  }
}

void playMotionOnce(int motion[][SV_NUM+1], int array_length, int sv_num){

  if(servoAvailable()){

    setMotion(motion[motion_status], sv_num);
    
    if(motion_status>=array_length-1){
      resetMotionStatus();
      setMotionNumber(999);
      return;
    }else{
      motion_status++;        //move to next status
    }
  }
}


//Read SENS_1or value
int readSens(int id){
  
  if(id > SENS_NUM || id <= 0){
    return 0;
  }else{
    int limit = 3;
    unsigned char addr = SENS_1+(id-1)*2;
    int data=0;
    while(limit){
      data = read2byte(addr);
      if(data <= 1023 && data >= 0){
        return data;
      }
      limit--;
    }
    return 0;
  }
}

int readPow(){
  unsigned char addr = POWER;
  return read2byte(addr); 
}

//Read current servo position
int readServoPos(int id){
  
  if(id > SV_NUM || id <= 0){
    return 0;
  }else{
    unsigned char addr = SV_1_POS+(id-1)*2;
    return read2byte(addr);
  }
}

//Read current servo counterclockwise limit
int readServoLimitL(){
  return read2byte(SV_L_LIMIT);
}

//Read current servo clockwise limit
int readServoLimitH(){
  return read2byte(SV_H_LIMIT);
}

//Read current servo offset
int readServoOffset(int id){

  if(id > SV_NUM || id <= 0){
    return 0;
  }else{
    unsigned char addr = SV_1_OFFSET+(id-1)*2;
    return read2byte(addr);
  }
}

//Read current servo moving time
int readServoMovingTime(){
  return read2byte(SV_MV_TIME);
}

int read2byte(unsigned char addr){

    //Write memmap address
    Wire.beginTransmission(DEV_ADDR);
    Wire.write(addr);
    Wire.endTransmission();
  
    //Read 2byte
    unsigned char tmp[2];
    int index = 0;
    Wire.requestFrom(DEV_ADDR, 2);
    while (Wire.available()) {
       tmp[index++]= Wire.read();
    }
    
    //Convert byte to short
    short data = tmp[1] << 8 | tmp[0];
    return data;
}

int servoAvailable(){
    unsigned char addr = BUF_STATUS;
    return !read1byte(addr);
}

int read1byte(unsigned char addr){

    //Write memmap address
    Wire.beginTransmission(DEV_ADDR);
    Wire.write(addr);
    Wire.endTransmission();
  
    //Read byte
    unsigned char tmp;
    Wire.requestFrom(DEV_ADDR, 1);
    while (Wire.available()) {
       tmp = Wire.read();
    }

    //Convert byte to short
    int data = (int)tmp;
    return data;
}

int powerOff(){
  write1byte(POW_OFF, 0x01);
}

int buzzerEnable(int flag){
  if(flag < 0){
    flag = 0;
  }else if(flag> 1){
    flag = 1;
  }
  unsigned char addr = BUZZER_ENABLE;
  write1byte(addr, flag);
  return 1;
}

int setBuzzer(int scale, int beat, int tang){
  if(scale < 0){
    scale = 0;
  }else if(scale> 88){
    scale = 88;
  }
  unsigned char addr = BUZZER_SCALE;
  write1byte(addr, scale);
  delay(beat);
  
  if(tang != 0){
    unsigned char addr = BUZZER_SCALE;
    write1byte(addr, scale);
    delay(beat - TANG_LENGTH);
    
    write1byte(addr, PN);
    delay(TANG_LENGTH);
  }else{
    unsigned char addr = BUZZER_SCALE;
    write1byte(addr, scale);
    delay(beat);
  }
  return 1;
}

int servoEnable(int id, int flag){
  if(id > SV_NUM || id <= 0){
    return 0;
  }else{
    unsigned char addr = PWM_ENABLE1+(id-1);
    write1byte(addr, flag);
    return 1;
  }
}

//Set servo target position (default range -1800 ~ 1800)
int setServoDeg(int id, int deg){
  
  if(id > SV_NUM || id <= 0){
    return 0;
  }else{
    unsigned char addr = SV_1_TPOS+(id-1)*2;
    write2byte(addr, deg);
    return 1;
  }
}

//Move all servos
int moveServo(){
  write1byte(SV_START, SV_FLAG);
}

//Move all servos
int stopServo(){
  write1byte(SV_CANCEL, SV_FLAG);
}

int setServoMode(int sv_mode){

  //Check limit
  if(sv_mode < MODE_OVERRIDE){
    sv_mode = MODE_OVERRIDE;
  }else if(sv_mode > MODE_SEQUENCE){
    sv_mode = MODE_SEQUENCE;
  }
  
  unsigned char addr = SV_MODE;
  write1byte(addr, sv_mode);
  return 1; 
}

int setServoLimitL(int deg){

  //Check limit
  if(deg < SV_LIMIT_MIN){
    deg = SV_LIMIT_MIN;
  }else if(deg > SV_LIMIT_MAX){
    deg = SV_LIMIT_MAX;
  }
  
  unsigned char addr = SV_L_LIMIT;
  write2byte(addr, deg);
  return 1; 
}

int setServoLimitH(int deg){

  //Check limit
  if(deg > SV_LIMIT_MAX){
    deg = SV_LIMIT_MAX;
  }else if(deg < SV_LIMIT_MIN){
    deg = SV_LIMIT_MIN;
  }
  
  unsigned char addr = SV_H_LIMIT;
  write2byte(addr, deg);
  return 1; 
}

//Set servo offset (range -500 ~ 500)
int setServoOffset(int id, int deg){

  if(deg < -OFFSET_LIMIT){
    deg = -OFFSET_LIMIT;
  }else if(deg > OFFSET_LIMIT){
deg = OFFSET_LIMIT;
  }

  if(id > SV_NUM || id < 0){
    return 0;
  }else{
    unsigned char addr = SV_1_OFFSET+(id-1)*2;
    write2byte(addr, deg);
    return 1;
  }
}

//Set servo movint time range 100 ~ 10000
int setServoMovingTime(int mv_time){

  //Check limit
  if(mv_time < SV_MV_TIME_L_LIMIT){
    mv_time = SV_MV_TIME_L_LIMIT;
  }else if(mv_time > SV_MV_TIME_H_LIMIT){
    mv_time = SV_MV_TIME_H_LIMIT;
  }
  //Send movint time
  write2byte(SV_MV_TIME, mv_time);
  return 1;
}

int setLedBrightness(int id, int brightness){

  if(brightness < 0){
    brightness = 0;
  }else if(brightness > LED_LIMIT){
    brightness = LED_LIMIT;
  }

  if(id > 12 || id < 1){
    return 0;
  }else{
    unsigned char addr = SV_1_TPOS+(id-1)*2;
    write2byte(addr, brightness);
    return 1;
  }
}

int setLedBrightnessDirect(int id, int brightness){

  if(brightness < 0){
    brightness = 0;
  }else if(brightness > LED_LIMIT){
    brightness = LED_LIMIT;
  }

  if(id > 12 || id < 1){
    return 0;
  }else{
    unsigned char addr = LED_BRIGHT1+(id-1)*2;
    write2byte(addr, brightness);
    return 1;
  }
}

int setLedMode(int id, int flag){

  if(flag < 0){
    flag = 0;
  }else if(flag > 1){
    flag = 1;
  }

  if(id > 12 || id < 1){
    return 0;
  }else{
    unsigned char addr = LED_MODE1+(id-1);
    write1byte(addr, flag);
    return 1;
  }
}

int setSensEnable(int flag){

  //Check limit
 if(flag == 0 || flag ==1){
    write1byte(SENS_ENABLE, flag);
  	return 1;
  }else{
  	return 0;
  }
}

int setPullupEnable(int id, int flag){

  //Check limit
  if(id < 1 || id > SENS_NUM){
    return 0;
  }else if(flag == 0 || flag ==1){
    write1byte(PULLUP_1+(id-1), flag);
  	return 1;
  }else{
  	return 0;
  }
}

int write2byte(unsigned char addr, short data){

  unsigned char upper_byte = data >> 8;
  unsigned char lower_byte = data;
  Wire.beginTransmission(DEV_ADDR);
  Wire.write(addr);
  Wire.write(lower_byte);
  Wire.write(upper_byte);
  Wire.endTransmission();
  return 1;
}

int write1byte(unsigned char addr, unsigned char data){

  Wire.beginTransmission(DEV_ADDR);
  Wire.write(addr);
  Wire.write(data);
  Wire.endTransmission();
  return 1;
}

int setMotion(int motion[SV_NUM+1]){
  
  unsigned char byte_motion[2*(SV_NUM+1)];
  int i;
  for(i=0;i<SV_NUM+1;i++){
    byte_motion[i*2] = motion[i];
    byte_motion[i*2+1] = motion[i] >> 8;
  }
  
  Wire.beginTransmission(DEV_ADDR);
  Wire.write(SV_MV_TIME);
  for(i=0;i<2*(SV_NUM+1);i++){
    Wire.write(byte_motion[i]);
  }
  Wire.endTransmission();

  Wire.beginTransmission(DEV_ADDR);
  Wire.write(SV_START);
  Wire.write(1);                  //SV_START
  Wire.endTransmission();

  return 1;
}

int setMotion(int motion[SV_NUM+1], int sv_num){
  
  unsigned char byte_motion[2*(sv_num+1)];
  int i;
  for(i=0;i<sv_num+1;i++){
    byte_motion[i*2] = motion[i];
    byte_motion[i*2+1] = motion[i] >> 8;
  }
  
  Wire.beginTransmission(DEV_ADDR);
  Wire.write(SV_MV_TIME);
  for(i=0;i<2*(sv_num+1);i++){
    Wire.write(byte_motion[i]);
  }
  Wire.endTransmission();

  Wire.beginTransmission(DEV_ADDR);
  Wire.write(SV_START);
  Wire.write(1);                  //SV_START
  Wire.endTransmission();

  return 1;
}



