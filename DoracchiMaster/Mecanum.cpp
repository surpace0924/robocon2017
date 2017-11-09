//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: メカナムホイールの出力値を計算する
// @Author: Ryoga Sato
// @Description: 
// 行列を用いた計算を行い、なめらかな移動を実現する
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Mecanum.hpp"

// 線形変換を表す行列（機体上部から見たホイールの回転方向に対応）
// 機体の各性能・重心に応じて任意に変更（フルで出力したければ1.0）
double g_coefMatrix[4][3] = {{-1.0,  1.0, -0.85},
                             {-1.0, -1.0, -0.85},
                             { 1.0, -1.0, -0.85},
                             { 1.0,  1.0, -0.85}};

void Mecanum::linearTransformation(int velocityVector[3], int maxOutputRate, int dir[4], int absOutputRate[4])
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
        dir[motorNum] = directions(outputRate[motorNum]);
        if (dir[motorNum] == BRAKE)
            absOutputRate[motorNum] = 0;
        else 
            absOutputRate[motorNum] = abs(outputRate[motorNum]);
    }
}
