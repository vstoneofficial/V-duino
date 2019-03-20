#include <vs-rc202.h>

void setup() {
  initLib();

  //setSensEnable(0);            //Disable Sens
  //setPullupEnable(1,1);        //Enable pullup of AN1
  //setPullupEnable(2,1);        //Enable pullup of AN2
  //setPullupEnable(3,0);        //Disable pullup of AN3

  Serial.begin(115200);
  Serial.println();
  Serial.println();
}

void loop() {

  int sens[5];
  sens[0] = readSens(1);      //Read sensor data from AN1 to AN3
  sens[1] = readSens(2);
  sens[2] = readSens(3);
  sens[3] = readPow();        //Read supply voltage
  sens[4] = (int)getDist();   //Get distance from sonic sensor

  Serial.print("sens1 : ");  //Show results
  Serial.print(sens[0]);
  Serial.print(" sens2 : ");
  Serial.print(sens[1]);
  Serial.print(" sens3 : ");
  Serial.print(sens[2]);
  Serial.print(" Supply_Vol : ");
  Serial.print(sens[3]);
  Serial.print(" sonic : ");
  Serial.print(sens[4]);
  Serial.println();
  delay(500);
}