//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: どらっち用の統括処理
// @Author: Ryoga Sato
// @Description:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <MsTimer2.h>

static int arg[4] = {0};
volatile int pastAngle[4] = {0};

void timer() {
    for(int i = 0; i < 4; i++) 
    {
        pastAngle[i] = arg[i];

    Serial.println(pastAngle[0]);
    }
}


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
    MsTimer2::set(500, timer);
    MsTimer2::start();

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

void move()
{
    // 出力値を格納
    int pwm[4] = {0};
    
    // スティックの値を速度ベクトルに代入
    int velocityVector[3];
    for (int i = 0; i < 3; i++)
        velocityVector[i] = (abs(propo.getStickVal(i)) > STICK_TH) ? 1.3*propo.getStickVal(i) : 0;

#ifndef _USE_STEERING_
#ifdef _USE_MECANUM_
    mcnum.calculate(velocityVector, MT_MAXPOWER, pwm);
    tx.sendData(pwm, MOVE_SERIALPORT);
    tx.confirmData(velocityVector, pwm);
#endif
#endif

#ifndef _USE_MECANUM_
#ifdef _USE_STEERING_
    steer.calculate(velocityVector, MT_MAXPOWER, pwm, arg);
    tx.sendData(pwm, arg, MOVE_SERIALPORT);
    tx.confirmData(velocityVector, pwm, arg);
#endif
#endif
}
