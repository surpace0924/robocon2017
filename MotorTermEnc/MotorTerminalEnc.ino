//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: モータターミナルを駆動させるためのプログラム
// @Date: 2017/10/21
// @Author: Ryoga Sato
// @Version: 1.0
// @Description:
// フルN、PN混合両方のMDを駆動できる
// settings.hpp以外のファイルは書き換え禁止！！！！
// @Update:
// @TODO:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "settings.hpp"

#include "StdPid.hpp"
Pid pid;

// 通信・時間管理
#define SERIAL_TIMEOUT 100
#define BAUNDRATE 57600
#define DEADTIME 3 * 8

// 出力管理
#define FREE 0b00
#define CW 0b01
#define CCW 0b10
#define BRK 0b11

#define KP 2.5
#define KI 0.05
#define KD 0

// PIN管理
#define ERROR_LED_PIN 13
const int OUTPUT_PIN[2][3] = {{5, 6, 7}, {10, 11, 12}};

// 各パラメータ（要素は多めにとっておく）
int dir[4];
int pwm[4];
int arg[4];
int rcvData[20];
int len;

void setup()
{
    Serial.begin(BAUNDRATE);
    TCCR0B = (TCCR0B & B11111000) + B010;
    TCCR1A = (TCCR1A & B11111100) + B01;
    TCCR1B = (TCCR1B & B11100000) + B01010;
    TCCR2A = (TCCR1C & B11111100) + B11;
    TCCR2B = (TCCR1C & B11110000) + B0010;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            pinMode(OUTPUT_PIN[i][j], OUTPUT);

    pinMode(ERROR_LED_PIN, OUTPUT);
    initEncoder();
}

void loop()
{
    while (1)
    {
        int nowAngle = getAngle() / 2;
        if (recieveData())
        {

            // 角度計算には第1象限と第4象限のみ使用（-90~90[deg]）
            int targetAngle = (arg[USE_MOTOR] > 90) ? arg[USE_MOTOR] - 180 : arg[USE_MOTOR];

            int output = pid.calculate(targetAngle, nowAngle, KP, KI, 0, 250);

            int steerAngleDir;
            if (output > 0)
                steerAngleDir = CW;
            else if (output < 0)
                steerAngleDir = CCW;
            else
                steerAngleDir = BRK;

            if (arg[USE_MOTOR] > 90)
            {
                if (dir[USE_MOTOR] == CW)
                    dir[USE_MOTOR] = CCW;
                else if (dir[USE_MOTOR] == CCW)
                    dir[USE_MOTOR] = CW;
                else
                    dir[USE_MOTOR] = BRK;
            }

            // 出力
            driveMotorOfFN(steerAngleDir, abs(output), 0);

            if (abs(output) < 50)
                driveMotorOfFN(dir[USE_MOTOR], pwm[USE_MOTOR], 1);
            else
                driveMotorOfFN(BRK, pwm[USE_MOTOR], 1);
            

            // デバッグ
            Serial.print(arg[USE_MOTOR]);
            Serial.print(" ");
            Serial.print(targetAngle);
            Serial.print(" ");
            if (dir[USE_MOTOR] == CCW)
                Serial.print(-1 * pwm[USE_MOTOR]);
            else
                Serial.print(pwm[USE_MOTOR]);
            Serial.print(" ");
            Serial.println(output);

            digitalWrite(ERROR_LED_PIN, LOW);
        }
        else
        {
            // データの受信が正しく行われていない場合はエラーLEDを点灯させる
            // Serial.println("failed");
            digitalWrite(ERROR_LED_PIN, HIGH);
        }
    }
}
