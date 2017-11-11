//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: データをソフトウェアシリアルを用いて他のマイコンまたはPCへ送信する
// @Author: Ryoga Sato
// @Description: 
// 送信用のPIN配置は[TX, RX, GND]
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef TransceiverForMDTerminal
#define TransceiverForMDTerminal

#include <Arduino.h>
#include "Universal.hpp"


// 回転方向系
#define LIMIT 254

class Transceiver
{
public:
    void sendData(int pwm[], int arg[], int usePort);
    void sendData(int pwm[], int usePort);
    void confirmData(int v[], int pwm[]);
    void confirmData(int v[], int pwm[], int arg[]);

private:
};

#endif // TransceiverForMDTerminal
