#define WIRE_CLK      400000  //I2C clock 400kHz
#define DEV_ADDR      0x50    //Device address

//Register address
#define SENS_ENABLE   0x00
#define POW_OFF       0x01
#define P_SW          0x02
#define POW_ENABLE    0x03
#define SENS_1        0x04
#define SENS_2        0x06
#define SENS_3        0x08
#define PULLUP_1      0x0a
#define PULLUP_2      0x0b
#define PULLUP_3      0x0c

#define POWER         0x0e
#define P_TH          0x10

#define SV_L_LIMIT    0x12
#define SV_H_LIMIT    0x14

#define SV_1_OFFSET   0x16
#define SV_2_OFFSET   0x18
#define SV_3_OFFSET   0x1a
#define SV_4_OFFSET   0x1c
#define SV_5_OFFSET   0x1e
#define SV_6_OFFSET   0x20
#define SV_7_OFFSET   0x22
#define SV_8_OFFSET   0x24
#define SV_9_OFFSET   0x26
#define SV_10_OFFSET  0x28

#define SV_1_POS      0x2a
#define SV_2_POS      0x2c
#define SV_3_POS      0x2e
#define SV_4_POS      0x30
#define SV_5_POS      0x32
#define SV_6_POS      0x34
#define SV_7_POS      0x36
#define SV_8_POS      0x38
#define SV_9_POS      0x3a
#define SV_10_POS     0x3c

#define PWM_ENABLE1   0x3e
#define PWM_ENABLE2   0x3f
#define PWM_ENABLE3   0x40
#define PWM_ENABLE4   0x41
#define PWM_ENABLE5   0x42
#define PWM_ENABLE6   0x43
#define PWM_ENABLE7   0x44
#define PWM_ENABLE8   0x45
#define PWM_ENABLE9   0x46
#define PWM_ENABLE10  0x47

#define SV_MV_TIME    0x48
#define SV_1_TPOS     0x4a
#define SV_2_TPOS     0x4c
#define SV_3_TPOS     0x4e
#define SV_4_TPOS     0x50
#define SV_5_TPOS     0x52
#define SV_6_TPOS     0x54
#define SV_7_TPOS     0x56
#define SV_8_TPOS     0x58
#define SV_9_TPOS     0x5a
#define SV_10_TPOS    0x5c

#define SV_START      0x5e
#define SV_CANCEL     0x5f
#define SV_STATUS     0x60
#define BUF_STATUS    0x61
#define SV_MODE       0x62

#define LED_MODE1     0x64
#define LED_MODE2     0x65
#define LED_MODE3     0x66
#define LED_MODE4     0x67
#define LED_MODE5     0x68
#define LED_MODE6     0x69
#define LED_MODE7     0x6a
#define LED_MODE8     0x6b
#define LED_MODE9     0x6c
#define LED_MODE10    0x6d

#define LED_BRIGHT1   0x6e
#define LED_BRIGHT2   0x70
#define LED_BRIGHT3   0x72
#define LED_BRIGHT4   0x74
#define LED_BRIGHT5   0x76
#define LED_BRIGHT6   0x78
#define LED_BRIGHT7   0x7a
#define LED_BRIGHT8   0x7c
#define LED_BRIGHT9   0x7e
#define LED_BRIGHT10  0x80

#define BUZZER_ENABLE 0x82
#define BUZZER_SCALE  0x83

#define SENS_NUM            3       //Number of sensor
#define SV_LIMIT_MIN        -2500      
#define SV_LIMIT_MAX        2500
#define OFFSET_LIMIT        500
#define SV_NUM              10      //Number of servo
#define SV_MV_TIME_L_LIMIT  40
#define SV_MV_TIME_H_LIMIT  10000
#define BUFSIZE             127
#define LED_LIMIT           1000
#define MODE_OVERRIDE       0x00
#define MODE_SEQUENCE       0x01
#define SV_FLAG             0x01    
#define TRIG 14                    //SONIC trig pin
#define ECHO 12                    //SONIC echo pin

//Buzzer
#define TANG_LENGTH 20
#define BEAT1 1000
#define BEAT2 BEAT1/2
#define BEAT4 BEAT1/4
#define BEAT8 BEAT1/8
#define SLUR 0
#define TANG 1

//piano key number
#define PN     0       //No sound
#define PA0    1
#define PA0_SH 2
#define PB0    3
#define PC1    4
#define PC1_SH 5
#define PD1    6
#define PD1_SH 7
#define PE1    8
#define PF1    9
#define PF1_SH 10
#define PG1    11
#define PG1_SH 12

#define PA1    13
#define PA1_SH 14
#define PB1    15
#define PC2    16
#define PC2_SH 17
#define PD2    18
#define PD2_SH 19
#define PE2    20
#define PF2    21
#define PF2_SH 22
#define PG2    23
#define PG2_SH 24

#define PA2    25
#define PA2_SH 26
#define PB2    27
#define PC3    28
#define PC3_SH 29
#define PD3    30
#define PD3_SH 31
#define PE3    32
#define PF3    33
#define PF3_SH 34
#define PG3    35
#define PG3_SH 36

#define PA3    37
#define PA3_SH 38
#define PB3    39
#define PC4    40
#define PC4_SH 41
#define PD4    42
#define PD4_SH 43
#define PE4    44
#define PF4    45
#define PF4_SH 46
#define PG4    47
#define PG4_SH 48

#define PA4    49
#define PA4_SH 50
#define PB4    51
#define PC5    52
#define PC5_SH 53
#define PD5    54
#define PD5_SH 55
#define PE5    56
#define PF5    57
#define PF5_SH 58
#define PG5    59
#define PG5_SH 60

#define PA5    61
#define PA5_SH 62
#define PB5    63
#define PC6    64
#define PC6_SH 65
#define PD6    66
#define PD6_SH 67
#define PE6    68
#define PF6    69
#define PF6_SH 70
#define PG6    71
#define PG6_SH 72

#define PA6    73
#define PA6_SH 74
#define PB6    75
#define PC7    76
#define PC7_SH 77
#define PD7    78
#define PD7_SH 79
#define PE7    80
#define PF7    81
#define PF7_SH 82
#define PG7    83
#define PG7_SH 84

#define PA7    85
#define PA7_SH 86
#define PB7    87
#define PC8    88

void initLib();
float getDist();
int setSensEnable(int flag);
int setPullupEnable(int id, int flag);
int readSens(int id);
int readPow();
int powerOff();
int readServoPos(int id);
int readServoLimitL();
int readServoLimitH();
int readServoOffset(int id);
int readServoMovingTime();
int servoEnable(int id, int flag);
int setServoDeg(int id, int deg);
int setServoMovingTime(int mv_time);
int setMotion(int motion[SV_NUM+1]);
int setMotion(int motion[SV_NUM+1], int sv_num);
int moveServo();
int stopServo();
int setServoMode(int sv_mode);
int setServoLimitL(int deg);
int setServoLimitH(int deg);
int setServoOffset(int id, int deg);
void setMotionNumber(int a);
int getMotionNumber();
void resetMotionStatus();
int servoAvailable();
void playMotion(int motion[][SV_NUM+1], int array_length);
void playMotion(int motion[][SV_NUM+1], int array_length,int sv_num);
void playMotionOnce(int motion[][SV_NUM+1], int array_length);
void playMotionOnce(int motion[][SV_NUM+1], int array_length,int sv_num);
int setLedMode(int id, int flag);
int setLedBrightness(int id, int brightness);
int setLedBrightnessDirect(int id, int brightness);
int buzzerEnable(int flag);
int setBuzzer(int scale, int beat, int tang);
int read2byte(unsigned char addr);
int read1byte(unsigned char addr);
int write2byte(unsigned char addr, short data);
int write1byte(unsigned char addr, unsigned char data);

