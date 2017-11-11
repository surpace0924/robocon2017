//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: 定数や構造体型をまとめて定義するヘッダ
// @Author: Ryoga Sato
// @Description:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _CONFIG_
#define _CONFIG_

// 移動機構の選択（使用する方のコメントアウトを外す、両方外すと動かない）
// #define _USE_MECANUM_
#define _USE_STEERING_

// シリアル通信のボーレート
#define BAUDRATE 57600

// 移動に使用するシリアルポート（0~3）
#define MOVE_SERIALPORT 1

// スティックの操作を受け付ける閾値
#define STICK_TH 20

// 攻撃機構に対応しているピン
#define ARM_CYLINDER_PIN A8
#define BURST_CYLINDER_PIN A9
#define BURST_ROD_PIN A10

// モータの最大出力
#define MT_MAXPOWER 250

#pragma once
#endif
