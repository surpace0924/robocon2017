//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: データをソフトウェアシリアルを用いて他のマイコンまたはPCへ送信する
// @Date: 2017/10/28
// @Author: Ryoga Sato
// @Version: 4.0
// @Description:
// 送信用のPIN配置は[TX, RX, GND]
// @Update:
//  11/01 Ver4.0
//    ステアリング処理を実装
//  10/08 Ver3.2
//    初期化関数を廃止 SerialPortのOpenはsetup関数内で事前に行うこと
//  07/23 Ver3.1
//    ハードウェアシリアルの設定処理を追加
//  07/23 Ver3.0
//    UNO,Mega両方に対応
//  07/05 Ver2.0
//    シリアルモニタによるデバッグを実装
//  06/25 Ver1.4
//    新型通信プログラムを開発
//    従来の通信方式が使用できなくなった
// @TODO:
//  MDTarminal搭載マイコンをPICからArduinoNanoへ移行中 回路が完成次第通信処理を変更予定
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "TransceiverForMotorTerm.hpp"
/**
モータデータを他のマイコンに送る
@since 1.0.0
@param
int dir[]: 方向
int pwm[]: PWM出力[0-100]
int usePort: 送信に使用するポート 0→Serial, 1→Serial1, 2→Serial2
@return
**/
void Transceiver::sendDataForSteer(int pwm[], int arg[], int usePort)
{
    unsigned char packet[15] = {0}; // 送信データ（パケット）
    int sum = 0;
    int i, j = 0;

    int motorNum = 4;


    packet[0] = 255; // スタートバイト
    packet[1] = 12;  // データのバイト長

    i = 2;
    j = 0;
    while (i <= 8)
    {
        packet[i++] = directions(pwm[j]);
        packet[i++] = abs(pwm[j++]);
    }
    
    Serial.print(abs(pwm[0]));
    Serial.println(packet[3]);

    for (int i = 0; i < 4; i++)
    {
        packet[i + 10] = arg[i];
    }

    // チェックサムの計算
    for (i = 2; i <= 13; i++)
        sum ^= packet[i];

    // チェックサムが255にならないようにする
    packet[14] = (sum != 255) ? sum : 254;

    // Serial.print(sum);
    // Serial.print(" ");
    // Serial.println(packet[14]);

    for (i = 0; i <= 14; i++)
    {
        // ポート別に送信
        if (usePort == 0)
        {
            Serial.print(packet[i]);
            Serial.print(" ");
        }
        else if (usePort == 1)
        {
            Serial1.write(packet[i]);
        }
        else if (usePort == 2)
        {
            Serial2.write(packet[i]);
        }
    }
    // Serial.println();
}

void Transceiver::confirmDataForSteerBySerialMonitor(int v[], int pwm[], int arg[])
{
    for (int i = 0; i < 3; i++)
    {
        Serial.print(v[i]);
        Serial.print(",");
    }

    for (int i = 0; i < 4; i++)
    {
        Serial.print(arg[i]);
        Serial.print(",");
        Serial.print(pwm[i]);
        if (i != 3)
            Serial.print(",");
    }
    Serial.print("\r");
}

void Transceiver::sendDataForMecanum(int pwm[], int usePort)
{
    unsigned char packet[20] = {0}; // 送信データ（パケット）
    int sum = 0;
    int i, j = 0;

    int motorNum = 4;

    packet[0] = 255;          // スタートバイト
    packet[1] = motorNum * 2; // データのバイト長

    i = 2;
    j = 0;
    while (i <= motorNum * 2)
    {
        packet[i++] = directions(pwm[j]);
        packet[i++] = abs(pwm[j++]);
    }

    // チェックサムの計算
    for (i = 2; i <= motorNum * motorNum + 1; i++)
        sum ^= packet[i];

    // チェックサムが255にならないようにする
    if (sum != 255)
        packet[motorNum * 2 + 2] = sum;
    else
        packet[motorNum * 2 + 2] = LIMIT;

    for (i = 0; i <= motorNum * 2 + 2; i++)
    {
        // ポート別に送信
        if (usePort == 0)
        {
            Serial.write(packet[i]);
        }
        else if (usePort == 1)
        {
            Serial1.write(packet[i]);
        }
        else if (usePort == 2)
        {
            Serial2.write(packet[i]);
        }
    }
}

/**
送信するデータをシリアルプロッタから確認
@since 2.0.0
@param
int dir[]: 方向
int pwm[]: PWM出力[0-100]
@return
**/
void Transceiver::confirmDataBySerialPlotter(int pwm[])
{
    for (int i = 0; i < 4; i++)
    {
        Serial.print(pwm[i]);
        Serial.print(" ");
    }
    Serial.println();
}
