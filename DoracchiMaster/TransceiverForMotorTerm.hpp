//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: データをソフトウェアシリアルを用いて他のマイコンまたはPCへ送信する
// @Date: 2017/10/28
// @Author: Ryoga Sato
// @Version: 3.2
// @Description: 
// 送信用のPIN配置は[TX, RX, GND]
// @Update:
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
#ifndef TransceiverForMDTerminal
#define TransceiverForMDTerminal

#include <Arduino.h>
#include "Universal.hpp"


// 回転方向系
#define LIMIT 254

class Transceiver
{
public:
    void sendDataForSteer(int pwm[], int arg[], int usePort);
    void confirmDataForSteerBySerialMonitor(int v[], int pwm[], int arg[]);
    void sendDataForMecanum(int pwm[], int usePort);
    void confirmDataBySerialMonitor(int dir[], int pwm[]);
    void confirmDataBySerialPlotter(int pwm[]);

private:
};

#endif // TransceiverForMDTerminal
