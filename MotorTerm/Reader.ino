#ifdef _USE_STEERING_
bool recieveData()
{
    unsigned long startTime = millis();

    while (millis() - startTime < SERIAL_TIMEOUT)
    {
        if (Serial.read() == 255)
        {
            startTime = millis();

            // 受信待機
            while (!Serial.available())
                if (millis() - startTime > SERIAL_TIMEOUT)
                    return false;

            // データ長を取得
            len = Serial.read();

            while (Serial.available() < 12 + 1)
                if (millis() - startTime > SERIAL_TIMEOUT)
                    return false;

            // データ長だけデータを受け付ける
            // 同時にデータの排他的論理総和を取る
            int bufSum = 0;
            for (int i = 0; i < 12; i++)
            {
                rcvData[i] = Serial.read();
                bufSum ^= rcvData[i];
            }

            // 必要なデータが送られてきた直後にはチェックサムが送られてくるので取得
            int checkSum = Serial.read();

            // データの排他的論理総和とチェックサムが一致するかを確認
            // チェックサムが255の場合は代わりに254が送られてくるのでそれにも対応
            if (((checkSum ^ bufSum) == 0) || ((checkSum ^ bufSum - 1) == 0))
            {
                // 一致 グローバル変数に書き込む

                dir[0] = rcvData[0];
                pwm[0] = rcvData[1];
                dir[1] = rcvData[2];
                pwm[1] = rcvData[3];
                dir[2] = rcvData[4];
                pwm[2] = rcvData[5];
                dir[3] = rcvData[6];
                pwm[3] = rcvData[7];
                arg[0] = rcvData[8];
                arg[1] = rcvData[9];
                arg[2] = rcvData[10];
                arg[3] = rcvData[11];

                return true;
            }
            else
            {
                // 不一致 falseで返す
                return false;
            }
        }
    }
    return false;
}

#else

bool recieveData()
{
    unsigned long startTime = millis();

    while (millis() - startTime < SERIAL_TIMEOUT)
    {
        if (Serial.read() == 255)
        {
            startTime = millis();

            // 受信待機
            while (!Serial.available())
                if (millis() - startTime > SERIAL_TIMEOUT)
                    return false;

            // データ長を取得
            len = Serial.read();

            while (Serial.available() < len + 1)
                if (millis() - startTime > SERIAL_TIMEOUT)
                    return false;

            // データ長だけデータを受け付ける
            // 同時にデータの排他的論理総和を取る
            int bufSum = 0;
            for (int i = 0; i < len; i++)
            {
                rcvData[i] = Serial.read();
                bufSum ^= rcvData[i];
            }

            // 必要なデータが送られてきた直後にはチェックサムが送られてくるので取得
            int checkSum = Serial.read();

            // データの排他的論理総和とチェックサムが一致するかを確認
            // チェックサムが255の場合は代わりに254が送られてくるのでそれにも対応
            if (((checkSum ^ bufSum) == 0) || ((checkSum ^ bufSum - 1) == 0))
            {
                // 一致 グローバル変数に書き込む
                for (int i = 0; i < len / 2; i++)
                {
                    dir[i] = rcvData[i * 2];
                    pwm[i] = rcvData[i * 2 + 1];
                }

                return true;
            }
            else
            {
                // 不一致 falseで返す
                return false;
            }
        }
    }
    return false;
}
#endif