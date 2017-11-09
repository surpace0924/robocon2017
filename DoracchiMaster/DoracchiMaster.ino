//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: どらっち用の統括処理
// @Date:
// @Author: Ryoga Sato
// @Version: 13.0
// @Description: コントローラから受け取ったデータをメカナムプログラムに
//    竿の展開を２つのスイッチの操作で展開させるようにした渡し、戻り値を送信用プログラムに受け渡す
// @TODO:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Universal.hpp"
#include "Config.hpp"

#include "Mecanum.hpp"
Mecanum mcnum;

#include "Steering.hpp"
Steering steer;

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
        driveSteer();
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
    static int arg[4] = {0};

    // スティックの値を速度ベクトルに代入
    int velocityVector[3];
    for (int i = 0; i < 3; i++)
        velocityVector[i] = (abs(propo.getStickVal(i)) < STICK_TH) ? 0 : propo.getStickVal(i);

    // 計算
    steer.calculate(velocityVector, 250, dir, pwm, arg);

    // 移動データを送信
    // tx.sendDataForSteer(dir, pwm, arg, 0);
    tx.sendDataForSteer(dir, pwm, arg, 1);
    tx.confirmDataForSteerBySerialMonitor(velocityVector, dir, pwm, arg);

    for (int i = 0; i < 4; i++)
        if ((dir[i] != BRAKE) && (pwm[i] > 0))
            return true;

    return false;
}
