/*アームの処理*/
#ifndef _WEAPON_
#define _WEAPON_

#include "Arduino.h"

class Arm
{
public:
    static const int CYLINDER_PIN = A8;
    void controlBySW(int SWVal1, int SWVal2);
    bool isAttacked;
private:
    bool autoAttack(bool reset);
    void down();
    void up();
};

class Burst
{
public:
    static const int CYLINDER_PIN = A9;
    static const int ROD_PIN = A10;
    void controlBySW(int cylinderSW, int rodSW);
private:
    void lift(bool needs);
    void expand(bool needs);
};

#endif
