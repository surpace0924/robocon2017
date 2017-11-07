//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: どらっち用の統括処理
// @Date:
// @Author: Ryoga Sato
// @Version: 13.0
// @Description: コントローラから受け取ったデータをメカナムプログラムに
//    竿の展開を２つのスイッチの操作で展開させるようにした渡し、戻り値を送信用プログラムに受け渡す
// @Update:
//  10/28 Ver13.0
//    メカナムではなく4輪ステアリングになった
//  10/26 Ver12.0
//    全国大会に向けてプログラムの設計を変更
//    コントローラの回路を分離して通信で値を取得するようにした
//  09/21 Ver11.0
//    一晩でアームが変わった
//    回転処理がいらなくなった
//  09/20 Ver10.0
//    竿の展開を２つのスイッチの操作で展開させるようにした
//    アームの回転パラメータを変えた
//  09/16 Ver9.0
//    アームの回転パラメータを変えた
//  09/05 Ver8.0
//    アームの回転動作をMegaに統合
//  08/28 Ver7.1
//    不必要な処理を削除、リファクタリングを実施
//  08/28 Ver7.0
//    コントローラ追加
//  08/25 Ver6.0
//    自動移動モードを廃止
//    コントローラ追加を見越してPropoのプログラムをクラス化
//    プロポのキー配置を大幅変更
//  08/22 Ver5.1
//    プロポのキー配置を若干変更
//    自動移動中の機構展開処理を実装
//    処理の簡単化
//  08/19 Ver5.0
//    PS3コンのプログラムを廃止、プロポ専用に
//    プロポのキー配置を大幅変更
//  08/09 Ver4.0
//    新型のクラスを正式採用
//  07/23 Ver3.0
//    新型のクラスを試作
//  07/05 Ver2.0
//    アームの駆動方式を変更
//  06/26 Ver1.5
//    自動加速モードを実装
//  06/25 Ver1.4
//    新型通信プログラムを開発
//    従来の通信方式が使用できなくなった
//  06/20 Ver1.3
//    シリンダにPWMを加えることにした
//    回路の変更に対応
//    PROPO、PS3コンの切り替えをマクロの定義だけで変更できるようにした
//
// @TODO:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <math.h>
#include "Config.hpp"

#include "Conversion.hpp"
PolarCoordinates coordinate;
MotorManagement motor;

#include "ReaderForPropoTerm.hpp"
Reader propo;

#include "TransceiverForMotorTerm.hpp"
Transceiver tx;

#include "Weapon.hpp"
Arm arm;
Burst burst;

void setup()
{
    pinMode(arm.CYLINDER_PIN, OUTPUT);
    pinMode(burst.CYLINDER_PIN, OUTPUT);
    pinMode(burst.ROD_PIN, OUTPUT);

    coordinate.setStickThreshold(STICK_TH);
    motor.setStickThreshold(STICK_TH);

    for (int i = 0; i < 6; i++)
        pinMode(DEBUG_LED_PIN_LIST[i], OUTPUT);

    Serial.begin(BAUDRATE);
    Serial1.begin(BAUDRATE);
    Serial2.begin(BAUDRATE);
}

void loop()
{
    if (propo.recieveControllerData())
    {
        // アームの制御
        arm.controlBySW(propo.getSwitchVal(1), propo.getSwitchVal(2));

        // 4点バーストの制御
        burst.controlBySW(propo.getSwitchVal(3), propo.getSwitchVal(4));

        // ステアを駆動させて警告
        warnByLED(driveSteer());
    }
    else
    {
        // Serial.println("failed!");
    }
}

bool driveSteer()
{
    // 出力値を格納
    int dir[4] = {0};
    int pwm[4] = {0};
    int arg[4] = {0};

    // スティックの値を速度ベクトルに代入
    int velocityVector[3];
    for (int i = 0; i < 3; i++)
        velocityVector[i] = (abs(propo.getStickVal(i)) < STICK_TH) ? 0 : propo.getStickVal(i);

    calculate(velocityVector, 250, dir, pwm, arg);

    // Serial.println(dir[0]);

    // 移動データを送信
//    tx.sendDataForSteer(dir, pwm, arg, 0);
    tx.sendDataForSteer(dir, pwm, arg, 1);
    // tx.confirmDataBySerialMonitor(dir, pwm);
    // tx.confirmDataBySerialPlotter(dir, pwm);

    tx.confirmDataForSteerBySerialMonitor(velocityVector, dir, pwm, arg);
    for (int i = 0; i < 4; i++)
        if ((dir[i] != BRK) && (pwm[i] > 0))
            return true;

    return false;
}

void calculate(int _velocityVector[3], int maxOutputRate, int _dir[4], int _pwm[4], int _arg[4])
{
    if (_velocityVector[0] == 0 && _velocityVector[1] == 0)
    {
        // 旋回成分のみ
        int i = 0;
        _arg[i++] = 145;
        _arg[i++] = 55;
        _arg[i++] = 145;
        _arg[i++] = 55;

        for (int i = 0; i < 4; i++)
        {
          // こうなるらしい
          if(i == 2 || i == 3){
            if (motor.getDir(_velocityVector[2]) == FORWARD)
            {
              _dir[i] = BACKWARD;
            } else if (motor.getDir(_velocityVector[2]) == BACKWARD){
              _dir[i] = FORWARD; 
            } else {
              _dir[i] = motor.getDir(_velocityVector[2]); 
            }
          
          }else{
            _dir[i] = motor.getDir(_velocityVector[2]);
          }  
            _pwm[i] = abs(_velocityVector[2]);
        }
    }
    else
    {
        int theta = map(_velocityVector[2], -255, 255, -90, 90);
        int coefficient = abs(map(_velocityVector[2], -255, 255, -90, 90));

        if (theta < 0)
            theta = theta + 360;

        int power[4][2] = {0};
        //0
        power[0][0] = _velocityVector[0] + coefficient * sin(coordinate.toRadian(theta));
        power[0][1] = _velocityVector[1] - coefficient * cos(coordinate.toRadian(theta));

        //1
        power[1][0] = _velocityVector[0] + coefficient * cos(coordinate.toRadian(theta));
        power[1][1] = _velocityVector[1] + coefficient * sin(coordinate.toRadian(theta));

        //2
        power[2][0] = _velocityVector[0] - coefficient * sin(coordinate.toRadian(theta));
        power[2][1] = _velocityVector[1] + coefficient * sin(coordinate.toRadian(theta));

        //3
        power[3][0] = _velocityVector[0] - coefficient * cos(coordinate.toRadian(theta));
        power[3][1] = _velocityVector[1] - coefficient * sin(coordinate.toRadian(theta));

        bool isOverflowOfOutputRate = false;
        double maxPwm = 0;
        double bufPwm[4] = {0};
        for (int i = 0; i < 4; i++)
        {
            _arg[i] = coordinate.getAngle(power[i][0], power[i][1]);
            _arg[i] = (_arg[i] < 180) ? _arg[i] : _arg[i] - 180;
            _dir[i] = (coordinate.getAngle(power[i][0], power[i][1]) < 180) ? FORWARD : BACKWARD;
            bufPwm[i] = abs(coordinate.getRadius(power[i][0], power[i][1]));

            // 最大値を格納
            maxPwm = (bufPwm[i] > maxPwm) ? bufPwm[i] : maxPwm;

            // いずれかのモータが出力倍率を超過していればフラグを立てる
            if (bufPwm[i] > 250)
                isOverflowOfOutputRate = true;
        }

        if (isOverflowOfOutputRate)
            for (int i = 0; i < 4; i++)
                _pwm[i] = map(bufPwm[i], 0, maxPwm, 0, 250);
        else
            for (int i = 0; i < 4; i++)
                _pwm[i] = bufPwm[i];
    }
}

void warnByLED(bool needs)
{
    if (needs)
        digitalWrite(DEBUG_LED_PIN_LIST[5], HIGH);
    else
        digitalWrite(DEBUG_LED_PIN_LIST[5], LOW);
}
