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


int usePort;
unsigned char data[2][16] = {0};

Transceiver::Transceiver(int port)
{
    usePort = port;
}

void Transceiver::set(int num, int type, int _data, bool needsFree)
{
    if(type == PWM) 
    {
        int state;
        if (_data > 0)
            state = FORWARD;
        else if (_data < 0)
            state = BACKWARD;
        else
            state = BRK;
    
        if (needsFree)
            state = FREE;

        data[0][num] = (0<<7) | (num << 3) | (0<<2) | state;
        data[1][num] = constrain(_data, 0, 253);
    } 
    else
    {
        data[0][num] = (num << 3) + (1<<2) + ((_data&0b1100000000)>>8);
        data[1][num] = _data&0b11111111;
    }
}



void Transceiver::send()
{
    int sum = 0;
 
    int motorNum = 4;

    unsigned char packet[33];

    packet[0] = OST;
 
    for (int i = 0; i <= 15; i++)
    {
        packet[2*i+1] = data[0][i];
        sum ^= data[0][i];
        packet[2*i+2] = data[1][i];
        sum ^= data[1][i];
    }

    // チェックサムが255にならないようにする
    packet[33] = (sum != 255) ? sum : 254;

    for (int i = 0; i <= 33; i++) {
        // ポート別に送信
        if (usePort == 0)
        {
            Serial.write(packet[i]);
            // Serial.print(packet[i]);
            // Serial.print(" ");
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

// void Transceiver::send()
// {
//     unsigned char packet[15] = {0}; // 送信データ（パケット）
//     int sum = 0;
//     int i, j = 0;

//     int motorNum = 4;

//     packet[0] = 255;  // スタートバイト
//     packet[1] = 12;    // データのバイト長

//     i = 2;
//     j = 0;
//     while(i <= 8) {
//         packet[i++] = dir[j];
//         packet[i++] = pwm[j++];
//     }
    
//     for (int i = 0; i < 4; i++)
//     {
//         packet[i+10] = arg[i];
//     }

//     // チェックサムの計算
//     for (i = 2; i <= 13; i++)
//         sum ^= packet[i];

//     // チェックサムが255にならないようにする
//     packet[14] = (sum != 255) ? sum : 254;

//     // Serial.print(sum);
//     // Serial.print(" ");
//     // Serial.println(packet[14]);

//     for (i = 0; i <= 14; i++) {
//         // ポート別に送信
//         if (usePort == 0)
//         {
//             Serial.print(packet[i]);
//         }
//         else if (usePort == 1)
//         {
//             Serial1.write(packet[i]);
//         }
//         else if (usePort == 2)
//         {
//             Serial2.write(packet[i]);
//         }
//     }
// }
