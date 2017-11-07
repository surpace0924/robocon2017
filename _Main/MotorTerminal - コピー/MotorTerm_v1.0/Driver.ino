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
void driveMotorOfFN()
{
    int i, j = 0;
    for (i = 0; i < 2; i++)
    {
        switch (dir[USE_MOTOR[i]])
        {
        case CW:
            digitalWrite(OUTPUT_PIN[i][j++], LOW);
            analogWrite(OUTPUT_PIN[i][j++], constrain(pwm[USE_MOTOR[i]], 0, 250));
            analogWrite(OUTPUT_PIN[i][j++], 0);
            break;
        case CCW:
            digitalWrite(OUTPUT_PIN[i][j++], LOW);
            analogWrite(OUTPUT_PIN[i][j++], 0);
            analogWrite(OUTPUT_PIN[i][j++], constrain(pwm[USE_MOTOR[i]], 0, 250));
            break;
        case BRK:
            digitalWrite(OUTPUT_PIN[i][j++], LOW);
            analogWrite(OUTPUT_PIN[i][j++], 0);
            analogWrite(OUTPUT_PIN[i][j++], 0);
            break;
        default:
            digitalWrite(OUTPUT_PIN[i][j++], HIGH);
            analogWrite(OUTPUT_PIN[i][j++], 0);
            analogWrite(OUTPUT_PIN[i][j++], 0);
            break;
        }
        j = 0;
    }
}


// PN混合driver用
void driveMotorOfPN()
{
    // デッドタイム処理
    static int lastDir[2] = {BRK};
    for (int i = 0; i < 2; i++)
    {
        if (lastDir[i] != dir[USE_MOTOR[i]])
        {
            for (int j = 0; j < 2; j++)
                for(int k = 0; k < 4; k++)
                    digitalWrite(OUTPUT_PIN[i][j++], LOW);
            delay(DEADTIME);
        }
        lastDir[i] = dir[USE_MOTOR[i]];
    }

    int i, j = 0;
    for (i = 0; i < 2; i++)
    {
        switch (dir[USE_MOTOR[i]])
        {
        case CW:
            analogWrite(OUTPUT_PIN[i][j++], pwm[USE_MOTOR[i]]);
            digitalWrite(OUTPUT_PIN[i][j++], HIGH);
            analogWrite(OUTPUT_PIN[i][j++], 0);
            digitalWrite(OUTPUT_PIN[i][j++], LOW);
            break;
        case CCW:
            analogWrite(OUTPUT_PIN[i][j++], 0);
            digitalWrite(OUTPUT_PIN[i][j++], LOW);
            analogWrite(OUTPUT_PIN[i][j++], pwm[USE_MOTOR[i]]);
            digitalWrite(OUTPUT_PIN[i][j++], HIGH);
            break;
        case BRK:
            analogWrite(OUTPUT_PIN[i][j++], 255);
            digitalWrite(OUTPUT_PIN[i][j++], LOW);
            analogWrite(OUTPUT_PIN[i][j++], 255);
            digitalWrite(OUTPUT_PIN[i][j++], LOW);
            break;
        default:
            analogWrite(OUTPUT_PIN[i][j++], 0);
            digitalWrite(OUTPUT_PIN[i][j++], LOW);
            analogWrite(OUTPUT_PIN[i][j++], 0);
            digitalWrite(OUTPUT_PIN[i][j++], LOW);
            break;
        }
        j = 0;
    }
}

