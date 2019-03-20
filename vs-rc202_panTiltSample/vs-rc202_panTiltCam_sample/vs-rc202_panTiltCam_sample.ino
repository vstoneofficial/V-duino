#include <ros.h>                            //rosのヘッダファイル
#include <std_msgs/String.h>                //文字列型メッセージ
#include <std_msgs/Empty.h>
#include <std_msgs/MultiArrayLayout.h>      //配列型メッセージ使用に必要
#include <std_msgs/MultiArrayDimension.h>   //配列型メッセージ使用に必要
#include <std_msgs/Int16MultiArray.h>       //Int16型配列メッセージ
#include <vs-rc202.h>

//サーボモータ最低制御周期
#define INTERVAL 40 //40ms以下の間隔での制御命令は受け付けない
//一定時間操作がないと脱力するためのパラメータ
#define RELAX_LIMIT 30000    //30秒間操作がなければ脱力

int sv_disable_flag = 1;    //サーボ脱力フラグ 1->非脱力 0->脱力

long pre_time = 0; //前回サーボを制御した時刻
int last_servo_deg[2] = { 0, 0};  //前回のサーボ指示角

//サーボのON,OFFを切り替える
void changeEnableServo(int flag){
  int i;
  for(i=1;i<=2;i++){
    servoEnable(i, flag);
  }
  sv_disable_flag = flag;   //現在サーボが脱力しているかのフラグ
}

//サーボモータの角度指令メッセージのコールバック関数
void jointCallback(const std_msgs::Int16MultiArray& msg) {
  //受信したメッセージは"msg"に格納されています
  int diff = millis() - pre_time;
  if(diff < INTERVAL){
    return;
  }

  if(last_servo_deg[0] != msg.data[0] || last_servo_deg[1] != msg.data[1]){
    pre_time = millis();

    //脱力している場合はPWM　ON
    if(!sv_disable_flag){
      changeEnableServo(1);
    }

    last_servo_deg[0] = msg.data[0];
    last_servo_deg[1] = msg.data[1];
    
    setServoDeg(1, msg.data[0]);
    setServoDeg(2, msg.data[1]);
    setServoMovingTime(INTERVAL+60); //Set moving time to the target position
    moveServo();
    
  }else if(diff > RELAX_LIMIT){
    if(sv_disable_flag){
      //changeEnableServo(0);
    }
  }
  
  return;
}

//ROSノードハンドル設定
ros::NodeHandle  nh; 

//サブスクライバー生成
ros::Subscriber<std_msgs::Int16MultiArray> sub("joint_degrees", &jointCallback);

//パブリッシャー生成
std_msgs::String str_msg; //文字列メッセージ
ros::Publisher chatter("chatter", &str_msg);  //パブリッシャー生成

char hello[13] = "hello world!";  //送信用文字列

void setup()
{
  //ROSセットアップ
  Serial.begin(115200);
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);

  initLib();                //Initilize vs-rc202 library
  servoEnable(1, 1);        //Enable SV1 PWM
  servoEnable(2, 1);        //Enable SV1 PWM
}

void loop()
{
  str_msg.data = hello;
  chatter.publish( &str_msg );  //メッセージパブリッシュ
  nh.spinOnce(); //ros spinOnce
  delay(50);  
}
