#ifndef _USE_PN_
#ifdef _USE_FN_
// フルN
void driveMotor(int _dir[], int _pwm[])
{
    int i, j = 0;
    for (i = 0; i < 2; i++)
    {
        switch (_dir[i])
        {
        case FREE:
            digitalWrite(OUTPUT_PIN[i][j++], HIGH);
            analogWrite(OUTPUT_PIN[i][j++], 0);
            analogWrite(OUTPUT_PIN[i][j++], 0);
            digitalWrite(OUTPUT_PIN[i][j++], HIGH);
            break;
        case FORWARD:
            digitalWrite(OUTPUT_PIN[i][j++], LOW);
            analogWrite(OUTPUT_PIN[i][j++], _pwm[i]);
            analogWrite(OUTPUT_PIN[i][j++], 0);
            digitalWrite(OUTPUT_PIN[i][j++], LOW);
            break;
        case BACKWARD:
            digitalWrite(OUTPUT_PIN[i][j++], LOW);
            analogWrite(OUTPUT_PIN[i][j++], 0);
            analogWrite(OUTPUT_PIN[i][j++], _pwm[i]);
            digitalWrite(OUTPUT_PIN[i][j++], LOW);
            break;
        default:
            digitalWrite(OUTPUT_PIN[i][j++], LOW);
            analogWrite(OUTPUT_PIN[i][j++], 0);
            analogWrite(OUTPUT_PIN[i][j++], 0);
            digitalWrite(OUTPUT_PIN[i][j++], LOW);
            break;
        }
        j = 0;
    }
}
#endif
#endif

#ifndef _USE_FN_
#ifdef _USE_PN_
void driveMotor(int _dir[], int _pwm[])
{
    // デッドタイム処理
    static int lastDir[2] = {BRAKE};
    for (int i = 0; i < 2; i++)
    {
        if (lastDir[i] != _dir[i])
        {
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 4; k++)
                    digitalWrite(OUTPUT_PIN[j][k], LOW);
            delay(DEADTIME);
        }
        lastDir[i] = _dir[i];
    }


    int i, j = 0;
    for (i = 0; i < 2; i++)
    {
        switch (dir[USE_MOTOR[i]])
        {
        case FORWARD:
            analogWrite(OUTPUT_PIN[i][j++], pwm[USE_MOTOR[i]]);
            digitalWrite(OUTPUT_PIN[i][j++], HIGH);
            analogWrite(OUTPUT_PIN[i][j++], 0);
            digitalWrite(OUTPUT_PIN[i][j++], LOW);
            break;
        case BACKWARD:
            analogWrite(OUTPUT_PIN[i][j++], 0);
            digitalWrite(OUTPUT_PIN[i][j++], LOW);
            analogWrite(OUTPUT_PIN[i][j++], pwm[USE_MOTOR[i]]);
            digitalWrite(OUTPUT_PIN[i][j++], HIGH);
            break;
        case BRAKE:
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
#endif
#endif
