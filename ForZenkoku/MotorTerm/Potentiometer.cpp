#include "Potentiometer.hpp"

// 開始値を格納
int pinOfSensor;
int mechanicalAngle;
int startPulse;

void Potentiometer::init(int pin, int maxAngle)
{
    mechanicalAngle = maxAngle;
    startPulse = analogRead(pinOfSensor);
}



int Potentiometer::getPulse()
{
    return analogRead(pinOfSensor);
}

int Potentiometer::getAbsoluteAngle()
{
    return (getPulse() * (mechanicalAngle / 1023.0));
}

int Potentiometer::getRelativeAngle()
{
    return (getPulse() - startPulse) * (mechanicalAngle / 1023.0);
}
