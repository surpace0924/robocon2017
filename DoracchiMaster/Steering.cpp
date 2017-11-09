//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: メカナムホイールの出力値を計算する
// @Author: Ryoga Sato
// @Description: 
// 行列を用いた計算を行い、なめらかな移動を実現する
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Steering.hpp"

void Steering::calculate(int _velocityVector[3], int maxOutputRate, int _dir[4], int _pwm[4], int _arg[4])
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
                if (directions(spinElement) == FORWARD)
                {
                    _dir[i] = BACKWARD;
                }
                else if (directions(spinElement) == BACKWARD)
                {
                    _dir[i] = FORWARD;
                }
                else
                {
                    _dir[i] = directions(spinElement);
                }
            }
            else
            {
                _dir[i] = directions(spinElement);
            }
            _pwm[i] = abs(spinElement);
        }
    }
    else
    {
        int angularVelocity = map(spinElement, -255, 255, -90, 90);
        int sign = (angularVelocity < 0) ? -1 : 1;

        int power[4][2] = {0};
        power[0][0] = xElement + sign * abs(angularVelocity * sin(radians(angularVelocity)));
        power[0][1] = yElement - sign * abs(angularVelocity * cos(radians(angularVelocity)));
        power[1][0] = xElement + sign * abs(angularVelocity * cos(radians(angularVelocity)));
        power[1][1] = yElement + sign * abs(angularVelocity * sin(radians(angularVelocity)));
        power[2][0] = xElement - sign * abs(angularVelocity * sin(radians(angularVelocity)));
        power[2][1] = yElement + sign * abs(angularVelocity * cos(radians(angularVelocity)));
        power[3][0] = xElement - sign * abs(angularVelocity * cos(radians(angularVelocity)));
        power[3][1] = yElement - sign * abs(angularVelocity * sin(radians(angularVelocity)));

        // 出力のガード
        bool isOverflowOfOutputRate = false;
        double maxPwm = 0;
        double bufPwm[4] = {0};
        for (int i = 0; i < 4; i++)
        {
            _arg[i] = angles(power[i][0], power[i][1]);
            _arg[i] = (_arg[i] < 180) ? _arg[i] : _arg[i] - 180;
            _dir[i] = (angles(power[i][0], power[i][1]) < 180) ? FORWARD : BACKWARD;
            bufPwm[i] = abs(radiuses(power[i][0], power[i][1]));

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
                             