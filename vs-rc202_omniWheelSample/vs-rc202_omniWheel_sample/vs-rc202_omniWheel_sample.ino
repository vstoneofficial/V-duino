#include <vs-rc202.h>

//ステータス（モーション）番号の設定
#define GET_WATER 1
#define SUN_L     2
#define SUN_R     3
#define NORMAL    4
#define SLEEP     5

#define INTERVAL  40    //moveOmuni3での移動時の制御周期

#define BEAT16    BEAT1/16  //16分音符の設定

int motion_time =  0;  //モーション再生時間
long pre_time = 0;      //直前の制御処理時刻
int led_mode = 0;       //LED点灯モード

//角度->ラジアン変換
double deg2rad(int deg){
  double rad;
  rad = deg * 3.14 /180;
  
  return rad;
}

//速度(velocity)、移動方向[°](axis)、旋回量(omega)から各サーボの回転速度を算出する
void moveOmuni3(int velocity, int axis, int omega){
  int v1, v2, v3;
  double vx, vy, rad;
  
  rad = deg2rad(axis);
  vx = velocity*cos(rad);
  vy = velocity*sin(rad);

  v1 = 0.5*vx + 0.865*vy + omega;
  v2 = -0.5*vx + 0.865*vy + omega;
  v3 = -vy + omega;
  
  setServoDeg(1, v1);
  setServoDeg(2, v2);
  setServoDeg(3, v3);
  setServoMovingTime(INTERVAL); //Set moving time
  motion_time = 0;
  moveServo();

  return;
}

void getWaterBuzzer(){
  setBuzzer(PG5, BEAT4, TANG);
  setBuzzer(PB5, BEAT8, TANG);
  setBuzzer(PB5, BEAT8, TANG);
  setBuzzer(PB5, BEAT8, TANG);
  setBuzzer(PA5, BEAT16, TANG);
  setBuzzer(PG5, BEAT16, TANG);
  setBuzzer(PD6, BEAT2, TANG);

  setBuzzer(PD6, BEAT16, TANG);
  setBuzzer(PC6, BEAT16, TANG);
  setBuzzer(PB5, BEAT8, TANG);
  setBuzzer(PB5, BEAT8, TANG);
  setBuzzer(PB5, BEAT8, TANG);
  setBuzzer(PA5, BEAT16, TANG);
  setBuzzer(PG5, BEAT16, TANG);
  setBuzzer(PD6, BEAT2, TANG);

  setBuzzer(PD6, BEAT16, TANG);
  setBuzzer(PC6, BEAT16, TANG);
  setBuzzer(PB5, BEAT8, TANG);
  setBuzzer(PC6, BEAT16, TANG);
  setBuzzer(PD6, BEAT16, TANG);
  setBuzzer(PC6, BEAT8, TANG);
  setBuzzer(PB5, BEAT8, TANG);
  setBuzzer(PA5, BEAT2, TANG);
}

int motionGetWater[16][11] = {
                  
                  {200,400,400,400,1000,0,1000,0,0,0,0},                  
                  {200,-400,-400,-400,0,1000,0,1000,0,0,0},
                  {200,400,400,400,1000,0,1000,0,0,0,0},
                  {200,-400,-400,-400,0,1000,0,1000,0,0,0},
                  {200,0,0,0,0,0,0,0,0,0,0},
                  {500,400,-400,0,1000,0,0,0,0,0,0}, 
                  {500,400,0,-400,0,1000,0,0,0,0,0},
                  {500,0,400,-400,0,0,1000,0,0,0,0},
                  {500,-400,0,400,0,0,0,1000,0,0,0},
                  {500,0,-400,400,1000,0,0,0,0,0,0},
                  {200,0,0,0,0,0,0,0,0,0,0},
                  {200,400,400,400,1000,0,1000,0,0,0,0},                  
                  {200,-400,-400,-400,0,1000,0,1000,0,0,0},
                  {200,400,400,400,1000,0,1000,0,0,0,0},
                  {200,-400,-400,-400,0,1000,0,1000,0,0,0},
                  {200,0,0,0,0,0,0,0,0,0,0},
                 };



void selectMotion(){
  
  switch(getMotionNumber()){              
    case GET_WATER:
      playMotionOnce(motionGetWater, 16);
      pre_time = millis();
      motion_time = 6000;
      break;
    case SUN_L:
      moveOmuni3(0, 0, 400);
      pre_time = millis();
      break;
    case SUN_R:
      moveOmuni3(0, 0, -400);
      pre_time = millis();
      break;
    case NORMAL:
      moveOmuni3(0, 0, 0);
  }
}

void getCommand(){
  int diff = millis() - pre_time;
  if(diff < motion_time){
    return;
  }  

  int sens[3];
  sens[0] = readSens(1)+120;  //CdS_L
  sens[1] = readSens(2);      //CdS_R
  sens[2] = readSens(3);      //water

  Serial.print("sens1 : ");  //Show results
  Serial.print(sens[0]);
  Serial.print(" sens2 : ");
  Serial.print(sens[1]);
  Serial.print(" sens3 : ");
  Serial.print(sens[2]);
  Serial.print(" diff : ");
  Serial.print(diff);
  Serial.println();

  if(sens[2] > 300){
    getWaterBuzzer();
    setMotionNumber(GET_WATER);
    led_mode = GET_WATER;
  }else if(abs(sens[0] - sens[1]) > 80){
    if(sens[0] > sens[1]){
      setMotionNumber(SUN_L);
      led_mode = SUN_L;
    }else{
      setMotionNumber(SUN_R);
      led_mode = SUN_R;
    }
  }else{
    setMotionNumber(NORMAL);
    led_mode = NORMAL;
  }

}

//LED点灯関数
int brightLedNo = 4;
int i = 0;
void brightLED(){
  
  if(i >= 20){
    setLedBrightnessDirect(4,0);   
    setLedBrightnessDirect(5,0);
    setLedBrightnessDirect(6,0);   
    setLedBrightnessDirect(7,0);
    
    switch(led_mode){    
      case GET_WATER:
      case NORMAL:
        break;
      case SUN_L:
        if(brightLedNo > 4){
          brightLedNo--;
        }else{
          brightLedNo = 7;
        }
        setLedBrightnessDirect(brightLedNo, 1000);
        break;
      case SUN_R:
        if(brightLedNo < 7){
          brightLedNo++;
        }else{
          brightLedNo = 4;
        }
        setLedBrightnessDirect(brightLedNo, 1000);
        break;
    }
    i=0;
  }else{
    i++;
  }

  return;
}


void setup() {
  initLib();
  buzzerEnable(1);

  //setSensEnable(0);            //Disable Sens
  //setPullupEnable(1,1);        //Enable pullup of AN1
  //setPullupEnable(2,1);
  //setPullupEnable(3,0);        //Disable pullup of AN3

  Serial.begin(115200);
  Serial.println();
  Serial.println();

  servoEnable(1, 1);        //Enable SV1 PWM
  servoEnable(2, 1);        //Enable SV2 PWM
  servoEnable(3, 1);        //Enable SV3 PWM
  servoEnable(4, 1);        //Enable SV4 PWM
  servoEnable(5, 1);        //Enable SV5 PWM
  servoEnable(6, 1);        //Enable SV6 PWM
  servoEnable(7, 1);        //Enable SV7 PWM

  setLedMode(4, 1);         //Set SV4 LED mode
  setLedMode(5, 1);         //Set SV5 LED mode
  setLedMode(6, 1);         //Set SV6 LED mode
  setLedMode(7, 1);         //Set SV7 LED mode

  setServoOffset(1, -190);   //Offset range:-500 to 500
  setServoOffset(2, -230);   //モータに合わせて設定してください
  setServoOffset(3, -270);

  //起動確認
  setLedBrightnessDirect(4,100);   //Turn on LED
  setLedBrightnessDirect(5,100);
  setLedBrightnessDirect(6,100);   
  setLedBrightnessDirect(7,100);
  delay(1000);
  setLedBrightnessDirect(4,0);   
  setLedBrightnessDirect(5,0);
  setLedBrightnessDirect(6,0);   
  setLedBrightnessDirect(7,0);
  delay(1000);
  
}

void loop() {

  getCommand();             //Read command
  selectMotion();           //Play motion
  brightLED();              //Set LED Brightness
  delay(10);
  
}
