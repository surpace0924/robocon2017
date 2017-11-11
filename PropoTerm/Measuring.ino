void getPinStates(void)
{
    int i;
    unsigned long loopTime = 0;                       // プログラム実行開始から信号を検出するループに入る時間を代入する変数
    bool nowPinState[SERVOSIG_NUM]  = {0};            // サーボ信号を受け取るarduinoの各ピンの現在のピン状態を代入(HIGHならばtrue、LOWならばfalse)
    bool lastPinState[SERVOSIG_NUM] = {0};            // 1回前のループのときのarduinoの各ピンの状態を代入する(2回のループで信号の変化を検出する感じ)
    unsigned long beginTimeArray[SERVOSIG_NUM] = {0}; // サーボ信号がLOWからHIGHになった時間を代入する
    unsigned long endTimeArray[SERVOSIG_NUM] = {0};   // サーボ信号のHIGHからLOWになった時間を代入する
    _continue:

    unsigned long current_time = micros();    // プログラム実行開始から現在までの時間を代入
    boolean needsContinuous = false;          // 信号がHIGHのままループを抜けることの無いようにループを継続するフラグ

    while ( ( ( loopTime = micros() ) - current_time) < PULSETIMEOUT || needsContinuous)
    {
        // 時間を扱うのでサーボ信号を検出している間は割り込みを禁止する
        noInterrupts();
        int i = 0;
            
        // 現在のピンの状態を代入する
        nowPinState[0] = bit_is_set(PIND,PIND5);
        nowPinState[1] = bit_is_set(PIND,PIND3);
        nowPinState[2] = bit_is_set(PIND,PIND2);
        nowPinState[3] = bit_is_set(PIND,PIND4);
        nowPinState[4] = bit_is_set(PIND,PIND6);
        nowPinState[5] = bit_is_set(PINB,PINB0);
        nowPinState[6] = bit_is_set(PINB,PINB1);
        nowPinState[7] = bit_is_set(PINB,PINB2);
        nowPinState[8] = bit_is_set(PINB,PINB3);

        for (i = 0; i < SERVOSIG_NUM; i++)
        {
            // 1回前のループのときのピンの状態と現在のピンの状態を比較して違ったら現在のピンの状態を見てそれに応じて時間を代入する
            if (nowPinState[i] != lastPinState[i])
            {
                if (nowPinState[i])
                    beginTimeArray[i] = loopTime;
                else
                    endTimeArray[i] = loopTime;
            }
        }
        needsContinuous = false;

        // サーボ信号を受け取る全てのピンの状態を見て、一つでもHIGHならばループ継続フラグを立てる
        for (i = 0; i < SERVOSIG_NUM; i++)
            needsContinuous |= nowPinState[i];

        // 現在のピンの状態を次のループのときに1回前のピンの状態として扱う
        for (i = 0; i < SERVOSIG_NUM; i++)
            lastPinState[i] = nowPinState[i];

        interrupts();
    }

    // フィルタ処理用の変数
    unsigned long nowSig[SERVOSIG_NUM];                 // 現在の信号
    static unsigned long lastSig[SERVOSIG_NUM] = {0};   // 前回の信号
    unsigned long filteredSig[SERVOSIG_NUM];            // フィルタ後の信号

    // 信号がHIGHととなる時間がマイナスになってしまうとアンダーフローしてしまうのでそれを防止する処理。もしマイナスになってたら再計測する。
    for (i = 0; i < SERVOSIG_NUM; i++)
    {
        if (endTimeArray[i] < beginTimeArray[i])
            goto _continue;

        // 取得した信号はとてもそのまま使えるような波形ではないためデジタルフィルタ（差分方程式方式）処理を行う
        // 現在の信号を取得
        nowSig[i] = endTimeArray[i] - beginTimeArray[i];
        // フィルタを行う
        filteredSig[i] = FILTER_COEFFICIENT * lastSig[i] + ((1-FILTER_COEFFICIENT) * nowSig[i]);
        // 次のループに備えて今回値を前回値として取っておく
        lastSig[i] = filteredSig[i];
    }

    // 上の処理で信号がHIGHとなる時間を値の範囲変換を行う関数の引数として扱い、その返り値を変数に代入
    for (i = 0; i < SERVOSIG_NUM - SWITCH_NUM; i++)
    {
        if (i == 1)
            g_stickVal[i] = -1*convertRangeOfStick(filteredSig[i]);
        else
            g_stickVal[i] = convertRangeOfStick(filteredSig[i]);
    }

    for (i = SERVOSIG_NUM - SWITCH_NUM; i < SERVOSIG_NUM; i++)
        g_stickVal[i] = convertRangeOfSwitch(filteredSig[i]);  // switchのデータを代入
}

// スティックの信号値を-254から254の間に納まるように範囲変換をする関数
int convertRangeOfStick(unsigned long propo_sig)
{
    if (propo_sig == 0)
        return 0;
    else
        return (int) constrain(map((long)propo_sig, 972, 2078, -254, 254), -254, 254);
}

int convertRangeOfSwitch(unsigned long propo_sig)
{
    if (propo_sig > 1700)
        return 0;
    else if (propo_sig > 1300)
        return 1;
    else
        return 2;
}

