//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: メカナムホイールの出力値を計算する
// @Date: 2017/07/23
// @Author: Ryoga Sato
// @Version: 2.0.0
// @Description: 
// 行列を用いた計算を行い、なめらかな移動を実現する
// @Update:
//  07/23 Ver2.0.0
//    クラス化
// @TODO:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _Mecanum_
#define _Mecanum_

#include <Arduino.h>
#include <math.h>


// 回転方向系
#define FREE 0b00
#define CW   0b01
#define CCW  0b10
#define BRK  0b11

// スティックの操作を受け付ける閾値
#define STICK_TH 30

class Mecanum
{
public:
    void setMecanumMatrix(double coefMatrix[4][3]);
    void calMecanumParam(int velocityVector[3], int maxOutputRate, int dir[4], int absOutputRate[4]);
    bool autoAcceleSystem(int stickVector[3], double spdLevel, int maxPower, int dir[], int pwm[], bool reset);
    int getRadius(double Xaxis, double Yaxis);
    double getAngle(double Xaxis, double Yaxis);
    int adjustMotorPower(int output, int th);
    int getMotorDir(int output, int th);
private:
};
 
#endif // StdMecanum