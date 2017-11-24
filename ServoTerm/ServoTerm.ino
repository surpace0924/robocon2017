#include <Servo.h>

// 各パラメータ（要素は多めにとっておく）
int dir[4];
int pwm[4];
int arg[4];
int rcvData[20];
int len;

#define SERIAL_TIMEOUT 100
#define BAUNDRATE 57600

#define CONVERT(val) map(val,0,180,0,265)

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
        int targetAngle[4] = {0};
        for(int i = 0; i < 4; i++){
          targetAngle[i] = arg[i];  
        }
        int outputSig[4] = {0};

       if(targetAngle[0] < 90)
          targetAngle[0] += 180;
        outputSig[0] = map((180-targetAngle[0]),-100,143,0,180);
        servo0.write(outputSig[0]);
        
       if(targetAngle[1] < 90)
          targetAngle[1] += 180;
        outputSig[1] = map((180-targetAngle[1]),-100,143,0,180);
        servo1.write(outputSig[1]);
        
       if(targetAngle[2] < 90)
          targetAngle[2] += 180;
        outputSig[2] = map((180-targetAngle[2]),-100,143,0,180);
        servo2.write(outputSig[2]); 

       if(targetAngle[3] < 90)
          targetAngle[3] += 180;
        outputSig[3] = map((180-targetAngle[3]),-100,143,0,180);
        servo3.write(outputSig[3]); 

        Serial.print(targetAngle[2]);
        Serial.print(" ");
        Serial.println(outputSig[2]);
    }
}
