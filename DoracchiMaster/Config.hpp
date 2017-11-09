//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: 定数や構造体型をまとめて定義するヘッダ
// @Date: 2017/08/09
// @Author: Ryoga Sato
// @Version: 4.0.0
// @Description: 
// @Update:
// @TODO:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef Config
#define Config

#define MC_MAXPOWER 255

// スティックの操作を受け付ける閾値
#define STICK_TH 20


const int BUZZER_PIN_LIST[3] = {49, 51, 53};

// デバッグ用LEDのPIN番号
const int DEBUG_LED_PIN_LIST[6] = {27, 23, 33, 37, 41, 45};




#endif // Config
