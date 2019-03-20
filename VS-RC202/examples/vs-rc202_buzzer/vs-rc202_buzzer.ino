#include <vs-rc202.h>

void setup() {

  initLib();                //Initilize vs-rc202 library
  buzzerEnable(1);          //Enable buzzer
                            //When buzzer is enabled SV9,10 cannot be used
}

void loop() {
  setBuzzer(PC5, BEAT4, TANG);
  setBuzzer(PC5, BEAT4, TANG);
  setBuzzer(PG5, BEAT4, TANG);
  setBuzzer(PG5, BEAT4, TANG);
  setBuzzer(PA5, BEAT4, TANG);
  setBuzzer(PA5, BEAT4, TANG);
  setBuzzer(PG5, BEAT2, TANG);

  setBuzzer(PF5, BEAT4, TANG);
  setBuzzer(PF5, BEAT4, TANG);
  setBuzzer(PE5, BEAT4, TANG);
  setBuzzer(PE5, BEAT4, TANG);
  setBuzzer(PD5, BEAT4, TANG);
  setBuzzer(PD5, BEAT4, TANG);
  setBuzzer(PC5, BEAT2, TANG);

  setBuzzer(PG5, BEAT4, TANG);
  setBuzzer(PG5, BEAT4, TANG);
  setBuzzer(PF5, BEAT4, TANG);
  setBuzzer(PF5, BEAT4, TANG);
  setBuzzer(PE5, BEAT4, TANG);
  setBuzzer(PE5, BEAT4, TANG);
  setBuzzer(PD5, BEAT2, TANG);

  setBuzzer(PG5, BEAT4, TANG);
  setBuzzer(PG5, BEAT4, TANG);
  setBuzzer(PF5, BEAT4, TANG);
  setBuzzer(PF5, BEAT4, TANG);
  setBuzzer(PE5, BEAT4, TANG);
  setBuzzer(PE5, BEAT4, TANG);
  setBuzzer(PD5, BEAT2, TANG);

  setBuzzer(PC5, BEAT4, TANG);
  setBuzzer(PC5, BEAT4, TANG);
  setBuzzer(PG5, BEAT4, TANG);
  setBuzzer(PG5, BEAT4, TANG);
  setBuzzer(PA5, BEAT4, TANG);
  setBuzzer(PA5, BEAT4, TANG);
  setBuzzer(PG5, BEAT2, TANG);

  setBuzzer(PF5, BEAT4, TANG);
  setBuzzer(PF5, BEAT4, TANG);
  setBuzzer(PE5, BEAT4, TANG);
  setBuzzer(PE5, BEAT4, TANG);
  setBuzzer(PD5, BEAT4, TANG);
  setBuzzer(PD5, BEAT4, TANG);
  setBuzzer(PC5, BEAT2, TANG);

  delay(500);
}
