//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: メインマイコンからモータターミナルに信号を送る処理
// @Date: 2017/10/21
// @Author: Ryoga Sato
// @Version: 1.0
// @Description: 
// 「#define Port」で使用するポートの書き換えができる。　そこ以外は書き換えないで！！
// @Update:
// @TODO:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ReaderForPropoTerminal
#define ReaderForPropoTerminal

#define Port Serial2

#include <Arduino.h>
#include <math.h>
#include "Config.hpp"

#ifdef ARDUINO_AVR_NANO
    #include <SoftwareSerial.h>
    SoftwareSerial Serial1(A2,A3);
    SoftwareSerial Serial2(A4,A5);
#endif

#ifdef ARDUINO_AVR_UNO
    #include <SoftwareSerial.h>
    SoftwareSerial Serial1(A2,A3);
    SoftwareSerial Serial2(A4,A5);
#endif

#define SERIAL_TIMEOUT 30

class Reader
{
public:
    bool recieveControllerData();
    int getStickVal(int parm);
    int getSwitchVal(int parm);

private:
};

#endif // ReaderForPropoTerminal