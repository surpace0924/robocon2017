#include <Servo.h>

// 各パラメータ（要素は多めにとっておく）
int dir[4];
int pwm[4];
int arg[4];
int rcvData[20];
int len;

#define SERIAL_TIMEOUT 100
#define BAUNDRATE 57600

Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;

void setup()
{
    Serial.begin(BAUNDRATE);
    servo0.attach(3);
    servo1.attach(5);
    servo2.attach(6);
    servo3.attach(11);
}

void loop()
{
    if (recieveData())
    {
        servo0.write(arg[3]); 
        servo1.write(arg[3]); 
        servo2.write(arg[3]); 
        servo3.write(arg[3]); 
    }
}
