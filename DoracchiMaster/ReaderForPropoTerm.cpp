//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: メインマイコンからモータターミナルに信号を送る処理
// @Date: 2017/10/21
// @Author: Ryoga Sato
// @Version: 1.0
// @Description: 
// 「#define Port」で使用するポートの書き換えができる。　そこ以外は書き換えないで！！
// @Update:
// @TODO:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "ReaderForPropoTerm.hpp"
int g_controllerData[10];
int rcvData[100];
int len;

bool Reader::recieveControllerData()
{
    unsigned long startTime = millis();

    while(millis() - startTime < SERIAL_TIMEOUT)
    {
        if(Port.read() == 255)
        {
            startTime = millis();

            // 受信待機
            while(!Port.available())
                if(millis() - startTime > SERIAL_TIMEOUT)
                    return false;
            
            // データ長を取得
            len = Port.read();
            
            while(Port.available() < len + 1)
                if(millis() - startTime > SERIAL_TIMEOUT)
                    return false;

            
            // データ長だけデータを受け付ける
            // 同時にデータの排他的論理総和を取る
            int bufSum = 0;
            for (int i = 0; i < len; i++) {
                rcvData[i] = Port.read();
                bufSum ^= rcvData[i];
            }


            // 必要なデータが送られてきた直後にはチェックサムが送られてくるので取得
            int checkSum = Port.read();
            
            // データの排他的論理総和とチェックサムが一致するかを確認
            // チェックサムが255の場合は変わりに254が送られてくるのでそれにも対応
            if(((checkSum ^ bufSum) == 0) || ((checkSum ^ bufSum-1) == 0)) {
                // 一致 グローバル変数に書き込む
                for(int i = 0; i < len; i++)
                    g_controllerData[i] = rcvData[i];  
                return true;
            } else {
                // 不一致 falseで返す
                return false;
            }
        }
    }
    return false;
}


int Reader::getStickVal(int parm)
{
    // 符号を比較
    if (((g_controllerData[0] >> parm) & 1) == 0)
        return  g_controllerData[parm+1];
    else
        return -g_controllerData[parm+1];        
}


int Reader::getSwitchVal(int parm)
{
    if (parm == 0)
        return (g_controllerData[0] >> 4);
    else
        return ((g_controllerData[5] >> (parm*2 - 2)) & 3);
}
