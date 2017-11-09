//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: 定数や構造体型をまとめて定義するヘッダ
// @Author: Ryoga Sato
// @Description:
//  いろんな関数に登場する処理をまとめて記述
//  とりあえずこれを#includeしておけばOK
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _UNIVERSAL_
#define _UNIVERSAL_

#include <Arduino.h>

#define MOTOR_MAXPOWER 250

// シリアル通信のボーレート
#define BAUDRATE 57600

// 回転方向系
#define FREE 0
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3

#define directions(output) ((output >= 0)?(FORWARD):(BACKWARD))
#define radiuses(x,y) (sqrt(x*x+y*y))
#define angles(x,y) ((atan2(y,x)<0)?(degrees(atan2(y,x)+2*M_PI)):(degrees(atan2(y,x))))

// int toDegree(double rad)
// {
//     return rad * 180 / M_PI;
// }

// double toRadian(int deg)
// {
//     return deg * M_PI / 180;
// }

// int getDir(int output, int th)
// {
//     if (output > th)
//         return FORWARD;
//     else if (output < (-1 * th))
//         return BACKWARD;
//     else
//         return BRAKE;
// }

// int getRadius(double Xaxis, double Yaxis)
// {
//     // 三平方の定理より求める
//     int r = sqrt(Xaxis * Xaxis + Yaxis * Yaxis);
//     return r;
// }

// int getAngle(double Xaxis, double Yaxis)
// {
//     double theta = atan2(Yaxis, Xaxis);
//     theta = atan2(Yaxis, Xaxis);

//     // θがマイナスになった場合2πを足す
//     if (theta < 0)
//         theta = theta + 2 * M_PI;
//     return toDegree(theta);
// }
#pragma once
#endif
