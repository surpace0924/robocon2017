/*パラメータ変換の処理*/
#ifndef _CONVERSION_
#define _CONVERSION_

#include "Arduino.h"
#include "Config.hpp"

class Conversion
{
public:
    int stickThreshold = 15;
    void setStickThreshold(int _stickThreshold);
private:
    
};

class PolarCoordinates : public Conversion {
public:
    int getRadius(double Xaxis, double Yaxis);
    int getAngle(double Xaxis, double Yaxis);
    int toDegree(double rad);
    double toRadian(int deg);
};

class MotorManagement : public Conversion {
public:
    int getDir(int output);
};

#endif
