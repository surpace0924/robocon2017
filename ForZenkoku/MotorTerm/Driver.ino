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