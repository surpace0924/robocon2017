//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: どらっち専用の攻撃機構駆動処理
// @Author: Ryoga Sato
// @Description: 
//  どらっち以外は削除してOK
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _WEAPON_
#define _WEAPON_

#include "Arduino.h"

class Arm
{
public:
    Arm(int pin);
    void controlBySW(int SWVal1, int SWVal2);
    bool isAttacked;
private:
    int CYLINDER_PIN;
    bool autoAttack(bool reset);
    void down();
    void up();
};

class Burst
{
public:
    Burst(int cylinderPin, int rodPin);
    void controlBySW(int cylinderSW, int rodSW);
private:
    int CYLINDER_PIN;
    int ROD_PIN;
    void lift(bool needs);
    void expand(bool needs);
};

#endif
