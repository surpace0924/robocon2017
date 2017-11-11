//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: メインマイコンからモータターミナルに信号を送る処理
// @Author: Ryoga Sato
// @Description: 
// 「#define Port」で使用するポートの書き換えができる。　そこ以外は書き換えないで！！
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ReaderForPropoTerminal
#define ReaderForPropoTerminal

#define Port Serial2

#include <Arduino.h>
#include "Universal.hpp"

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