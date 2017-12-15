//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: ポテンショメータ
// @Author: Ryoga Sato
// @Description:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef StdPotentiometer
#define StdPotentiometer

#include <Arduino.h>

// クラスの定義
class Potentiometer
{
public:
    void init(int pin, int maxAngle);
    int pinOfSensor;
    int mechanicalAngle;
    int startPulse;
    int getPulse();
    int getAbsoluteAngle();
    int getRelativeAngle();

private:
};
 
#endif // StdPotentiometer
