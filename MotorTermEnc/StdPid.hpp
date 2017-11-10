//////////////////////////////////////////////////////////////////////////////
// @Outline: PS3コンをUSB接続で使用するための基本コード
// @Date: 2017/3/18
// @Author: Ryoga Sato
// @Version: 1.0.0
// @Description: PS3コンからのデータを受け取り、各パラメータを構造体として格納
// @Update:
// @TODO: 即席で作ったからごちゃごちゃしてる。クラスの設計を再考
//////////////////////////////////////////////////////////////////////////////
#ifndef StdPid
#define StdPid

#include <Arduino.h>
#include <math.h>
#include "Config.hpp"

// クラスの定義
class Pid
{
public:
    int calculate (int setpoint, int input, double Kp, double Ki, double Kd, int max);

private:
};
 
#endif // StdPid