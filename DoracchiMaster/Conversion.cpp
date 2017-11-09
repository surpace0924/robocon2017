#include "Conversion.hpp"

void Conversion::setStickThreshold(int _stickThreshold)
{
    stickThreshold = _stickThreshold;
}

int PolarCoordinates::getRadius(double Xaxis, double Yaxis)
{
    // 三平方の定理より求める
    int r = sqrt(Xaxis * Xaxis + Yaxis * Yaxis);
    return r;
}

int PolarCoordinates::getAngle(double Xaxis, double Yaxis)
{
    double theta = atan2(Yaxis, Xaxis);
    theta = atan2(Yaxis, Xaxis);

    // θがマイナスになった場合2πを足す
    if (theta < 0)
        theta = theta + 2 * M_PI;
    return toDegree(theta);
}

int PolarCoordinates::toDegree(double rad)
{
    return rad * 180 / M_PI;
}

double PolarCoordinates::toRadian(int deg)
{
    return deg * M_PI / 180;
}


int MotorManagement::getDir(int output)
{
    if (output > stickThreshold)
        return FORWARD;
    else if (output < (-1 * stickThreshold))
        return BACKWARD;
    else
        return BRK;
}
