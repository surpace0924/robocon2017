//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: よく使う処理をマクロでまとめた
// @Author: Ryoga Sato
// @Description: 
//  がりょが作ったプログラム・ライブラリは基本的にこのファイルに依存しているので同じディレクトリに入れておく
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _UNIVERSAL_
#define _UNIVERSAL_

#include <Arduino.h>

#define MOTOR_MAXPOWER 250

// 回転方向系
#define FREE 0
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3

// 方向・偏角・動径の算出
#define directions(output) ((output==0)?(BRAKE):((output>0)?(FORWARD):(BACKWARD)))
#define radiuses(x,y) (sqrt(((x)*(x))+((y)*(y))))
#define angles(x,y) ((atan2(y,x)<0)?(degrees(atan2(y,x)+2*M_PI)):(degrees(atan2(y,x))))

#pragma once
#endif
