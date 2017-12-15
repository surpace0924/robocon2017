static inline void sendData(void)
{
    unsigned char packet[10] = {0}; // 送信データ（パケット）
    int sum = 0;
    int i = 0;

    packet[0] = 255;  // スタートバイト
    packet[1] = 6;    // データのバイト長

    // スティックの符号と絶対値をそれぞれのパケットに代入
    for (i = 0; i <= 3; i ++) {
        if (g_stickVal[i] < 0)
            packet[2] += (1 << i);

        // データが255だとスタートバイトと区別が付かなくなるのでガードする
        if (abs(g_stickVal[i]) != 255)
            packet[i+3] = abs(g_stickVal[i]);
        else 
            packet[i+3] = LIMIT;
    }

    // SW
    packet[2] += (g_stickVal[4] << 4);
    packet[7] += (g_stickVal[8] << 6) +(g_stickVal[7] << 4) + (g_stickVal[6] << 2) + g_stickVal[5];

    // チェックサムの計算
    for (i = 2; i <= 7; i++)
        sum ^= packet[i];

    // チェックサムが255にならないようにする
    if (sum != 255)
        packet[8] = sum;
    else
        packet[8] = LIMIT;

    // 最後にエンドバイトを挿入
    packet[9] = EOT;

    // パケットを順番に送信
    for (i = 0; i <= 9; i++)
        Serial.write(packet[i]);
}
