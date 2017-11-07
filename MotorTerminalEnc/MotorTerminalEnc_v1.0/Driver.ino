//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: 出力処理
// @Date: 2017/10/21
// @Author: Ryoga Sato
// @Version: 1.0
// @Description: 
// ボーレートは57600bps
// @Update:
// @TODO:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// フルNドライバ用
void driveMotorOfFN(int dir, int output, int port)
{
    int i = 0; 
    switch (dir)
    {
    case CW:
        analogWrite(OUTPUT_PIN[port][0], constrain(output, 0, 250));
        analogWrite(OUTPUT_PIN[port][1], 0);
        digitalWrite(OUTPUT_PIN[port][2], LOW);
        break;
    case CCW:
        analogWrite(OUTPUT_PIN[port][0], 0);
        analogWrite(OUTPUT_PIN[port][1], constrain(output, 0, 250));
        digitalWrite(OUTPUT_PIN[port][2], LOW);
        break;
    case BRK:
        analogWrite(OUTPUT_PIN[port][0], 0);
        analogWrite(OUTPUT_PIN[port][1], 0);
        digitalWrite(OUTPUT_PIN[port][2], LOW);
        break;
    default:
        analogWrite(OUTPUT_PIN[port][0], 0);
        analogWrite(OUTPUT_PIN[port][1], 0);
        digitalWrite(OUTPUT_PIN[port][2], HIGH);
        break;
    }
}

