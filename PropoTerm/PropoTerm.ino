//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: モータターミナルを駆動させるためのプログラム
// @Date: 2017/10/21
// @Author: Ryoga Sato
// @Version: 1.0
// @Description: 
// プログラムの書き換え禁止！！！！
// @Update:
// @TODO:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SERVOSIG_NUM 10
#define SWITCH_NUM 6
#define PULSETIMEOUT 20000
#define LIMIT 254
#define EOT 0x04
#define FILTER_COEFFICIENT 0.6

// プロポの値を格納
int g_stickVal[SERVOSIG_NUM] = {0};

void setup()
{
    for (int i = 2; i <= 11; i++)
        pinMode(i, INPUT);

    Serial.begin(57600);
}

void loop()
{
    while (1)
    {
        getPinStates(); // グローバル変数への値代入
        sendData();     // シリアル通信
    }
}
