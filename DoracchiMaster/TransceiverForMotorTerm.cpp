#include "TransceiverForMotorTerm.hpp"

void Transceiver::sendData(int pwm[], int usePort)
{
    unsigned char packet[20] = {0}; // 送信データ（パケット）
    int sum = 0;
    int i, j = 0;

    int motorNum = 4;

    int absPwm[4] = {0};
    for (int i = 0; i < 4; i++)
        absPwm[i] = abs(pwm[i]);

    packet[0] = 255;          // スタートバイト
    packet[1] = motorNum * 2; // データのバイト長

    i = 2;
    j = 0;
    while (i <= motorNum * 2)
    {
        packet[i++] = directions(pwm[j]);
        packet[i++] = absPwm[j++];
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
            Serial.write(packet[i]);
        else if (usePort == 1)
            Serial1.write(packet[i]);
        else if (usePort == 2)
            Serial2.write(packet[i]);
    }
}

void Transceiver::sendData(int pwm[], int arg[], int usePort)
{
    unsigned char packet[15] = {0}; // 送信データ（パケット）
    int sum = 0;
    int i, j = 0;

    int absPwm[4] = {0};
    for (int i = 0; i < 4; i++)
        absPwm[i] = abs(pwm[i]);

    packet[0] = 255; // スタートバイト
    packet[1] = 12;  // データのバイト長

    i = 2;
    j = 0;
    while (i <= 8)
    {
        packet[i++] = directions(pwm[j]);
        packet[i++] = absPwm[j++];
    }

    for (int i = 0; i < 4; i++)
        packet[i + 10] = arg[i];

    // チェックサムの計算
    for (i = 2; i <= 13; i++)
        sum ^= packet[i];

    // チェックサムが255にならないようにする
    packet[14] = (sum != 255) ? sum : 254;

    for (i = 0; i <= 14; i++)
    {
        // ポート別に送信
        if (usePort == 0)
            Serial.write(packet[i]);
        else if (usePort == 1)
            Serial1.write(packet[i]);
        else if (usePort == 2)
            Serial2.write(packet[i]);
    }
    // Serial.println();
}

void Transceiver::confirmData(int v[], int pwm[])
{
    for (int i = 0; i < 3; i++)
    {
        Serial.print(v[i]);
        Serial.print(",");
    }

    for (int i = 0; i < 4; i++)
    {
        Serial.print(pwm[i]);
        if (i != 3)
            Serial.print(",");
    }
    Serial.print("\n");
}

void Transceiver::confirmData(int v[], int pwm[], int arg[])
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
    Serial.print("\n");
}
