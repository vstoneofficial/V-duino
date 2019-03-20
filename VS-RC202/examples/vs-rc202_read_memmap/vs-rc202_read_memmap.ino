#include <vs-rc202.h>
#include <Wire.h>

void readSens(){

    Wire.beginTransmission(DEV_ADDR);
    Wire.write( SENS_1);
    Wire.endTransmission();
  
    //Read 2byte
    unsigned char tmp[6];
    int index = 0;
    Wire.requestFrom(DEV_ADDR, 6);
    while (Wire.available()) {
       tmp[index++]= Wire.read();
    }
    
    //Convert byte to short
    short sens1 = tmp[1] << 8 | tmp[0];
    short sens2 = tmp[3] << 8 | tmp[2];
    short sens3 = tmp[5] << 8 | tmp[4];

    //Display data
    Serial.print("sens1:");
    Serial.print(sens1);
    Serial.print("  sens2:");
    Serial.print(sens2);
    Serial.print("  sens3:");
    Serial.println(sens3);   
}

void setup(){

  Serial.begin(115200);
  initLib();
}

void loop(){
  readSens();
  delay(500);
}



