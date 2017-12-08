// PIDのやつ（たぶん正確じゃない）
#ifndef StdPid
#define StdPid

#include <Arduino.h>
#include <math.h>

// クラスの定義
class Pid
{
public:
    int calculate (int setpoint, int input, double Kp, double Ki, double Kd, int max);

private:
};
 
#endif // StdPid