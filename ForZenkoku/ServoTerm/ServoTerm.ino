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
        // 目標角を代入
        int targetAngle[4] = {0};
        for (int i = 0; i < 4; i++)
            targetAngle[i] = arg[i];  

        // 出力用信号を生成
        // サーボライブラリで180を渡すと229度まで回るので無理やり修正
        int outputSig[4] = {0};
        for(int i = 0; i < 4; i++)
        {
            targetAngle[i] += (targetAngle[i] < 90) ? 180 : 0;
            outputSig[i] = map((180-targetAngle[i]),-100,129,0,180);
        }

        // ライブラリに渡して出力
        servo0.write(outputSig[0]);
        servo1.write(outputSig[1]);
        servo2.write(outputSig[2]); 
        servo3.write(outputSig[3]);
    }
}
