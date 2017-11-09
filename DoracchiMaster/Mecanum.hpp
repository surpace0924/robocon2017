//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: メカナムホイールの出力値を計算する
// @Date: 2017/10/08
// @Author: Ryoga Sato
// @Version: 3.0
// @Description: 
// 行列を用いた計算を行い、なめらかな移動を実現する
// @Update:
//  10/08 Ver3.0
//    自動加速廃止
//  07/23 Ver2.0
//    クラス化
// @TODO:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef StdMecanum
#define StdMecanum

#include <Arduino.h>
#include "Universal.hpp"

class Mecanum
{
public:
    void linearTransformation(int velocityVector[3], int maxOutputRate, int dir[4], int absOutputRate[4]);
private:
};

#endif // StdMecanum
