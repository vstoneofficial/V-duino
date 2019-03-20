#include <vs-rc202.h>

void getCommand(){

  if(Serial.available()){
    char a = Serial.read();
    Serial.print(a);
    Serial.println();
    if(a == 'w'){
      servoEnable(1, 1);        //Enable SV1 PWM
      servoEnable(2, 1);        //Enable SV2 PWM
      servoEnable(3, 1);        //Enable SV3 PWM
      servoEnable(4, 1);        //Enable SV4 PWM
      Serial.println("Enable");
    }else if(a == 's'){
      servoEnable(1, 0);        //Disable SV1 PWM
      servoEnable(2, 0);        //Disable SV2 PWM
      servoEnable(3, 0);        //Disable SV3 PWM
      servoEnable(4, 0);        //Disable SV4 PWM
      Serial.println("Disable");
    }
    Serial.println();
    Serial.println("Enter Command w, s");
    Serial.print("$>");
  }
}

void setup() {
  initLib();                //Initilize vs-rc202 library
  servoEnable(1, 1);        //Enable SV1 PWM
  servoEnable(2, 1);        //Enable SV2 PWM
  servoEnable(3, 1);        //Enable SV3 PWM
  servoEnable(4, 1);        //Enable SV4 PWM

  Serial.begin(115200);     //Initialize UART
  Serial.println();
  Serial.println();
  Serial.println("Enter Command w,s");
  Serial.print("$>");
}

void loop() {
  getCommand();
}