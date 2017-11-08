//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: どらっち用の統括処理
// @Date:
// @Author: Ryoga Sato
// @Version: 13.0
// @Description: コントローラから受け取ったデータをメカナムプログラムに
//    竿の展開を２つのスイッチの操作で展開させるようにした渡し、戻り値を送信用プログラムに受け渡す
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
    static int dir[4] = {0};
    int pwm[4] = {0};
    int arg[4] = {0};

    // スティックの値を速度ベクトルに代入
    int velocityVector[3];
    for (int i = 0; i < 3; i++)
        velocityVector[i] = (abs(propo.getStickVal(i)) < STICK_TH) ? 0 : propo.getStickVal(i);

    // 計算
    calculate(velocityVector, 250, dir, pwm, arg);

    // 移動データを送信
    // tx.sendDataForSteer(dir, pwm, arg, 0);
    tx.sendDataForSteer(dir, pwm, arg, 1);
    tx.confirmDataForSteerBySerialMonitor(velocityVector, dir, pwm, arg);

    for (int i = 0; i < 4; i++)
        if ((dir[i] != BRK) && (pwm[i] > 0))
            return true;

    return false;
}

void calculate(int _velocityVector[3], int maxOutputRate, int _dir[4], int _pwm[4], int _arg[4])
{
    int xElement = _velocityVector[0];
    int yElement = _velocityVector[1];
    int spinElement = _velocityVector[2];

    if (xElement == 0 && yElement == 0 && spinElement != 0)
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
            if (i == 0 || i == 3)
            {
                if (motor.getDir(spinElement) == FORWARD)
                {
                    _dir[i] = BACKWARD;
                }
                else if (motor.getDir(spinElement) == BACKWARD)
                {
                    _dir[i] = FORWARD;
                }
                else
                {
                    _dir[i] = motor.getDir(spinElement);
                }
            }
            else
            {
                _dir[i] = motor.getDir(spinElement);
            }
            _pwm[i] = abs(spinElement);
        }
    }
    else
    {
        int angularVelocity = map(spinElement, -255, 255, -90, 90);
        int sign = (angularVelocity < 0) ? -1 : 1;

        int power[4][2] = {0};
        power[0][0] = xElement - sign * abs(angularVelocity * sin(coordinate.toRadian(angularVelocity)));
        power[0][1] = yElement + sign * abs(angularVelocity * cos(coordinate.toRadian(angularVelocity)));
        power[1][0] = xElement - sign * abs(angularVelocity * cos(coordinate.toRadian(angularVelocity)));
        power[1][1] = yElement - sign * abs(angularVelocity * sin(coordinate.toRadian(angularVelocity)));
        power[2][0] = xElement + sign * abs(angularVelocity * sin(coordinate.toRadian(angularVelocity)));
        power[2][1] = yElement - sign * abs(angularVelocity * cos(coordinate.toRadian(angularVelocity)));
        power[3][0] = xElement + sign * abs(angularVelocity * cos(coordinate.toRadian(angularVelocity)));
        power[3][1] = yElement + sign * abs(angularVelocity * sin(coordinate.toRadian(angularVelocity)));

        // 出力のガード
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
