//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: どらっち用の統括処理
// @Author: Ryoga Sato
// @Description:
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
Arm arm(ARM_CYLINDER_PIN);
Burst burst(BURST_CYLINDER_PIN, BURST_ROD_PIN);

void setup()
{
    pinMode(ARM_CYLINDER_PIN, OUTPUT);
    pinMode(BURST_CYLINDER_PIN, OUTPUT);
    pinMode(BURST_ROD_PIN, OUTPUT);

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
        move();
    }
    else
    {
        // Serial.println("failed!");
    }
}

int arg[4] = {0};
void move()
{
    // 出力値を格納
    int pwm[4] = {0};

    // スティックの値を速度ベクトルに代入
    int velocityVector[3];
    if(propo.getSwitchVal(0) == 2) 
    {
        for (int i = 0; i < 3; i++)
            velocityVector[i] = (abs(propo.getStickVal(i)) > STICK_TH) ? STICK_CORRECTION_FACTOR*propo.getStickVal(i) : 0;
    }
    else
    {
        velocityVector[0] = (abs(propo.getStickVal(0)) > STICK_TH) ? -1*STICK_CORRECTION_FACTOR*propo.getStickVal(0) : 0;
        velocityVector[1] = (abs(propo.getStickVal(1)) > STICK_TH) ? -1*STICK_CORRECTION_FACTOR*propo.getStickVal(1) : 0;
        velocityVector[2] = (abs(propo.getStickVal(2)) > STICK_TH) ? STICK_CORRECTION_FACTOR*propo.getStickVal(2) : 0;
    }

    steer.calculate(velocityVector, MT_MAXPOWER, pwm, arg);
    tx.sendData(pwm, arg, MOVE_SERIALPORT);
    tx.confirmData(velocityVector, pwm, arg);
}