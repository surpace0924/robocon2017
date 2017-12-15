#include "Pid.hpp"
int Pid::calculate (int setpoint, int input, double Kp, double Ki, double Kd, int maxVal)
{
    // 前回、今回の偏差値を格納
    static int deviation[2] = {0};
    // 今回の偏差を求める
    deviation[0] = setpoint - input;
    
    // 残留偏差を格納
    static double residualDeviation = 0;
    // 2回分の偏差値の平均値に呼び出しの周期をかけたものを累積させていき、疑似的に積分を行う
    residualDeviation += (deviation[1] + deviation[0]) / 2.0 * 10;
    residualDeviation = constrain(residualDeviation, -255, 255);

    // 各項の計算
    double proportionalTerm = Kp * deviation[0];
    double integralTerm = Ki * residualDeviation;
    double differentialTerm = Kd * (deviation[0] - deviation[1]);

    // Serial.print(differentialTerm);
    // Serial.print(",");

    // 各項を足して出力を決定する
    int output = (int)(proportionalTerm + integralTerm - differentialTerm);

    // 次回呼び出したときに今回の偏差値を過去の値として記憶しておく
    deviation[1] = deviation[0];

    return constrain(output, -1 * maxVal, maxVal);
}
