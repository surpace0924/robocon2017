//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: モータターミナルを駆動させるためのプログラム
// @Author: Ryoga Sato
// @Description:
// フルN、PN混合両方のMDを駆動できる
// settings.hpp以外のファイルは書き換え禁止！！！！
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Config.hpp"
#include "Universal.hpp"

#include "Potentiometer.hpp"
Potentiometer potentio;

#include "Pid.hpp"
Pid pid;

// 通信・時間管理
#define SERIAL_TIMEOUT 100
#define BAUNDRATE 57600
#define DEADTIME 3 * 8

#define KP 1.65
#define KI 0
#define KD 0

// PIN管理
#define ERROR_LED_PIN 13
const int OUTPUT_PIN[2][4] = {{3, 6, 5, 7}, {9, 11, 10, 12}};

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
        for (int j = 0; j < 4; j++)
            pinMode(OUTPUT_PIN[i][j], OUTPUT);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 4; j++)
            digitalWrite(OUTPUT_PIN[i][j], LOW);

    pinMode(ERROR_LED_PIN, OUTPUT);
    
    potentio.init(0, 270);

#ifdef _USE_POTENTIOMETER_
#ifdef _USE_FN_
        initEncoder();  
#endif
#endif
}

void loop()
{
    while (1)
    {
        if (recieveData())
        {
            int angle = 0;
#ifdef _USE_POTENTIOMETER_
            angle = -1*potentio.getRelativeAngle();
#else
#ifdef _USE_ENCODER_
            angle = getAngle() / 2;
#endif
#endif

#ifdef _USE_STEERING_
            //ステアリングを使用 
            controlDriverForSteering(angle);
#else
#ifdef _USE_MECANUM_
            // メカナムを使用
            controlDriverForMecanum();
#endif
#endif
            Serial.println(angle);
        }
        else
        {
            // Serial.println("failed");
        }
    }
}

// ステア用
void controlDriverForSteering(int nowAngle)
{
    // 第1象限と第4象限のみ使用（-90~90[deg]）
    int targetAngle = (arg[USE_MOTOR[0]] > 90) ? arg[USE_MOTOR[0]] - 180 : arg[USE_MOTOR[0]];
    int output = pid.calculate(targetAngle, nowAngle, KP, KI, KD, 250);

    if (arg[USE_MOTOR[0]] >= 90)
    {
        if (dir[USE_MOTOR[0]] == FORWARD)
            dir[USE_MOTOR[0]] = BACKWARD;
        else if (dir[USE_MOTOR[0]] == BACKWARD)
            dir[USE_MOTOR[0]] = FORWARD;
        else
            dir[USE_MOTOR[0]] = BRAKE;
    }
    if (arg[USE_MOTOR[1]] >= 90)
    {
        if (dir[USE_MOTOR[1]] == FORWARD)
            dir[USE_MOTOR[1]] = BACKWARD;
        else if (dir[USE_MOTOR[1]] == BACKWARD)
            dir[USE_MOTOR[1]] = FORWARD;
        else
            dir[USE_MOTOR[1]] = BRAKE;
    }

    int outputDir[2];
    int outputPwm[2];
    outputDir[0] = dir[USE_MOTOR[0]];
    outputPwm[0] = pwm[USE_MOTOR[0]];
    outputDir[1] = dir[USE_MOTOR[1]];
    outputPwm[1] = pwm[USE_MOTOR[1]];
//    outputDir[0] = directions(output);
//    outputPwm[0] = abs(output);
//    outputDir[1] = (abs(output) < 50) ? dir[USE_MOTOR[0]] : BRAKE;
//    outputPwm[1] = pwm[USE_MOTOR[0]];

    driveMotor(outputDir, outputPwm);
}

// メカナム用
void controlDriverForMecanum()
{
    int outputDir[2];
    int outputPwm[2];
    outputDir[0] = dir[USE_MOTOR[0]];
    outputPwm[0] = pwm[USE_MOTOR[0]];
    outputDir[1] = dir[USE_MOTOR[1]];
    outputPwm[1] = pwm[USE_MOTOR[1]];

    driveMotor(outputDir, outputPwm);
}
