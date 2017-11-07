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

// 通信・時間管理
#define SERIAL_TIMEOUT 2000
#define BAUNDRATE 57600
#define DEADTIME 3 * 8
#define OST 255

// 出力管理
#define FREE 0b00
#define CW 0b01
#define CCW 0b10
#define BRK 0b11

// 各パラメータ（要素は多めにとっておく）
int rcvData[100];
int type[16] = {0};
int state[16] = {0};
int pwm[16] = {0};
int arg[16] = {0};


// PIN管理
#define ERROR_LED_PIN 13
const int OUTPUT_PIN[2][4] = {{3, 6, 5, 7}, {9, 11, 10, 12}};


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

    pinMode(ERROR_LED_PIN, OUTPUT);
}

void loop()
{
    while (1)
    {
        if (recieveData())
        {

            Serial.println(rcvData[1]);

            // #ifdef FN
//             driveMotorOfFN();
// #endif

// #ifndef FN
//             driveMotorOfPN();
// #endif

            digitalWrite(ERROR_LED_PIN, LOW);
        }
        else
        {
            // データの受信が正しく行われていない場合はエラーLEDを点灯させる
            digitalWrite(ERROR_LED_PIN, HIGH);
            Serial.println("!!!!!");
            

        }
    }
}
