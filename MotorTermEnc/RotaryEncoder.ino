#include <math.h>
#define ENCODER_A 2 // ロータリーエンコーダのA相ピン割り当て
#define ENCODER_B 3 // ロータリーエンコーダのB相ピン割り当て
/**************設定部**************/
void initEncoder()
{
    pinMode(11, OUTPUT);
    digitalWrite(11, HIGH);

    // 外部割込み用のピンをプルアップで入力に設定
    pinMode(ENCODER_A, INPUT_PULLUP);
    pinMode(ENCODER_B, INPUT_PULLUP);

    // 外部割込み用のピンと関数、トリガを指定
    attachInterrupt(0, countALayer, CHANGE);
    attachInterrupt(1, countBLayer, CHANGE);
}


// パルス数を格納
volatile long g_pulse = 0;


/**************計測部**************/
void countALayer(void)
{
    volatile bool currEncB = digitalRead(ENCODER_B);
    volatile bool currEncA = digitalRead(ENCODER_A);
    volatile static bool oldEncB; // B相の前回値
    if (currEncA)
    {
        // 立ち上がり
        if (oldEncB && !currEncB)
            g_pulse--;
        else
            g_pulse++;
    }
    else
    {
        // 立ち下がり
        if (oldEncB && !currEncB)
            g_pulse++;
        else
            g_pulse--;
    }
    oldEncB = currEncB;
}


void countBLayer(void)
{
    volatile bool currEncB = digitalRead(ENCODER_B);
    volatile bool currEncA = digitalRead(ENCODER_A);
    volatile static bool oldEncA = 0; // A相の前回値

    if (currEncB)
    {
        if (oldEncA && !currEncA)
            g_pulse++;
        else
            g_pulse--;
    }
    else
    {
        if (oldEncA && !currEncA)
            g_pulse--;
        else
            g_pulse++;
    }
    oldEncA = currEncA;
}


int getPulseNum () 
{
    return g_pulse;
}

double getAngle () 
{
    return ((g_pulse * 360.0) / 400.0);
}
