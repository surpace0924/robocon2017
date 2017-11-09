#include "StdMecanum.hpp"
#include "StdTransceiverForMD.h"

// 各モータと要素に対応する回転方向、出力倍率を格納する配列（要するに係数行列）
// 機体の各性能・重心に応じて任意に変更（フルで出力したければ1.0）
double g_coefMatrix[4][3] = {0};


/**
@since 1.0.0
@param　double* 各モータと要素に対応する回転方向、出力倍率を格納する配列（の先頭のアドレス）
@return
**/
void Mecanum::setMecanumMatrix(double coefMatrix[4][3]) 
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            g_coefMatrix[i][j] = coefMatrix[i][j];
        }
    }
}


/**
引数に受け取ったスティックの要素をもとに4つのモータの出力比率のパラメータを演算させる
@since 1.0.0
@param
xAxis: X軸の値
yAxis: Y軸の値
spin: 回転成分の値
maxOutputRate: 出力の最大値
dir: 方向データが格納される配列
absOutputRate: 出力値データの絶対値が格納される配列
@return
**/
void Mecanum::calMecanumParam(int velocityVector[3], int maxOutputRate, int dir[4], int absOutputRate[4])
{
    // 行列計算を簡単にするために配列（線形変換前のベクトル）に代入する
    int outputRate[4];

    // スティックの要素と出力倍率や方向を勘案し、各モータの出力値を決める
    for (int motorNum = 0; motorNum < 4; motorNum++)
    {
        // 出力のレートを格納するバッファ変数  [-300.0 - 300.0]
        double bufOutputRate[4] = {0};

        // 理論出力レート値が実際の範囲越えを起こしたかを格納するフラグ変数
        bool isOverflowOfOutputRate = false;

        // 最大値を格納 [0-100]
        double MaxAbsOutputRate = 0;

        // 行列の積を求める
        for (int motorNum = 0; motorNum < 4; motorNum++)
        {
            for (int element = 0; element < 3; element++) {
                // 3つの要素の計算結果の総和をとる
                bufOutputRate[motorNum] += g_coefMatrix[motorNum][element] * velocityVector[element];
            }
        
            // 絶対値の最大値を格納
            MaxAbsOutputRate = (abs(bufOutputRate[motorNum]) > MaxAbsOutputRate) ? abs(bufOutputRate[motorNum]) : MaxAbsOutputRate;

            // いずれかのモータが出力倍率を超過していればフラグを立てる
            if (abs(bufOutputRate[motorNum]) > 100) {
                isOverflowOfOutputRate = true;
            }
        }

        // 出力値の最終調整
        // 1つでもモータが出力倍率を超過しているか？
        if (isOverflowOfOutputRate == true) {
            // 超過している
            // 出力値を再調整しつつ出力用の配列に書きこむ
            for (int motorNum = 0; motorNum < 4; motorNum++) {
                outputRate[motorNum] = constrain((bufOutputRate[motorNum] * (100 / MaxAbsOutputRate)), -100, 100) * maxOutputRate / 100;
            }
        } else {
            // 超過が存在しない
            // すべて出力範囲内で収まっているためそのまま書き込む
            for (int motorNum = 0; motorNum < 4; motorNum++) {
                outputRate[motorNum] = bufOutputRate[motorNum] * maxOutputRate / 100;
            }
        }
    }

    // 別関数より回転方向を得て結果を代入する
    // 出力比率を送信するときは符号が邪魔になるため消す
    for (int motorNum = 0; motorNum < 4; motorNum++)
    {
        dir[motorNum] = getMotorDir(outputRate[motorNum], 5);
        if (dir[motorNum] == BRK)
            absOutputRate[motorNum] = 100;
        else 
            absOutputRate[motorNum] = adjustMotorPower(abs(outputRate[motorNum]), 5);
    }
}


/**
オートアクセルシステム
@since 1.0.0
@param
@return
bool → AASをリセットする必要があるか
**/
bool Mecanum::autoAcceleSystem(int stickVector[3], double spdLevel, int maxPower, int dir[], int pwm[], bool reset)
{
    // マイコンの電源が入ってからAASが起動するまでの経過ミリ秒
    static unsigned long startTime;

    if (reset)
        startTime = millis();

    // AAS起動から今のループまでの経過ミリ秒（偏差）
    int deltaTime = millis() - startTime + 800;

    int xElms, yElms, spinElms;

    // 左スティックの位置を極座標系内の座標に見立てて角度(弧度法)を得る int[-255 ~ 255]
    double angleOfLeft = getAngle(stickVector[0], stickVector[1]);

    // 角度データと経過時間から出力計算用のX,Y成分を算出する
    if (getRadius(stickVector[0], stickVector[1]) >= STICK_TH) 
    {
        xElms = constrain(deltaTime * spdLevel, 0, 100) * cos(angleOfLeft);
        yElms = constrain(deltaTime * spdLevel, 0, 100) * sin(angleOfLeft);
    }
    else
    {
        xElms = 0;
        yElms = 0;
    }

    if (abs(stickVector[2]) >= STICK_TH)
        spinElms = constrain(deltaTime * spdLevel, 0, 100) * stickVector[2] / 100;
    else
        spinElms = 0;

    // ガード処理（後で時間があるときにマクロ化）
    if (abs(xElms) <= 5)    xElms = 0;
    if (abs(yElms) <= 5)    yElms = 0;
    if (abs(spinElms) <= 5) spinElms = 0;

    if (xElms == 0 && yElms == 0 && spinElms == 0)
    {
        // 全てのスティックが操作されていないとき
        deltaTime = 0;
        int zeroVector[3] = {0};
        calMecanumParam(zeroVector, maxPower, dir, pwm);
        return true;
    }

    int velocityVector[3] = {xElms, yElms, spinElms};
    calMecanumParam(velocityVector, maxPower, dir, pwm);

    return false;
}


/**
スティックの位置を極座標系内の半径(Radius)成分を求める
@since 1.0.0
@param
double Xaxis → 直交座標系でのX座標
double Yaxis → 直交座標系でのY座標
@return
int → 極座標系での半径成分 [0 ~ 255]
**/
int Mecanum::getRadius(double Xaxis, double Yaxis)
{
    // 三平方の定理より求める
    int r = sqrt(Xaxis * Xaxis + Yaxis * Yaxis);

    // 値を確実に範囲内に収める
    if (r > 255)
        return r = 255;
    else if (r < 0)
        return r = 0;
    else
        return r;
}


/**
スティックの位置を極座標系内の角度(Angle)成分を求める
@since 1.0.0
@param
double Xaxis → 直交座標系でのX座標
double Yaxis → 直交座標系でのY座標
@return
double theta → 極座標系での角度成分(単位は[rad]) [0 ~ 2π]
**/
double Mecanum::getAngle(double Xaxis, double Yaxis)
{
    double theta = atan2(Yaxis, Xaxis);

    // スティックの値が設定値以上であれば操作しているとみなす
    if (getRadius(Xaxis, Yaxis) >= STICK_TH)
    {
        theta = atan2(Yaxis, Xaxis);

        // θがマイナスになった場合2πを足す
        if (theta < 0)
            theta = theta + 2 * M_PI;
    }
    else
    {
        // 呼び出し側の関数では[0 ~ 2π]の範囲外の値が入ると操作対象外とするので適当な値を代入する
        theta = 100;
    }
    return theta;
}


/**
出力値を調整する
閾値以下の場合は0にし、マイナスの場合は絶対値をとる
@since 1.2.0
@param
int output analogWriteの出力値
int th 閾値（の絶対値）
@return
調整後の出力値（値は正）
**/
int Mecanum::adjustMotorPower(int output, int th)
{
    if (output > th)
        return output;
    else if (output < (-1 * th))
        return output * -1;
    else
        return 0;
}


/**
出力値の符号をもとにモータの回転方向を得る
閾値以下の場合はブレーキ
事前にCW、CCW、BRKのマクロ定義が必要
@since 1.2.0
@param
int output analogWriteの出力値
int th 閾値（の絶対値）
@return
調整後の出力値（値は正）
**/
int Mecanum::getMotorDir(int output, int th)
{
    if (output > th)
        return CW;
    else if (output < (-1 * th))
        return CCW;
    else
        return BRK;
}

