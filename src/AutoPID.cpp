#include "AutoPID.h"
#include "Arduino.h"

int AutoPID::MotorInput[2] = {10, 9};
int AutoPID::MotorOutput[2] = {11, 8};
int AutoPID::Sensors[5] = {A0, A1, A2, A3, A4};
int AutoPID::Motor[2] = {0};
bool AutoPID::Line[5] = {false};

void AutoPID::FollowLine()
{                      // Main action for the robot to follow the line
    GetSensorStatus(); // lay trang thai cua 5 sensor IR
    LinePIDFilter();
    ShiftSpeed(Motor);
}

void AutoPID::GetSensorStatus()
{ // Get all the sensor status
    for (int i = 0; i < 5; i++)
    {
        Line[i] = ReadLine(i);
    }
}

bool AutoPID::ReadLine(int index)
{ // Get the sensor status for each sensor
    int temp = analogRead(Sensors[index]);
    if (temp >= Sensor_HIGH)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void AutoPID::LinePIDFilter()
{ // PID control in line tracking mode
    static double kP = 39, kI = 0.005, kD = 30;
    static double gain = 100;
    static double prev_error = 0, prev_I = 0;
    double p = 0, i = 0, d = 0, pid_value;

    p = GetError(); // p thuc chat la error
    i = prev_I + p;
    d = p - prev_error;

    pid_value = kP * p + kI * i + kD * d;
    prev_I = i;
    prev_error = p;
    pid_value *= gain / 100;
    Motor[0] = INITIAL_SPEED + pid_value; // trai
    Motor[1] = INITIAL_SPEED - pid_value; // phai
}

// double AutoPID::SpeedPIDFilter(double PIDValue) // Slow down or spped up the robot when necessary
// {
//     static double kP = 0, kI = 0, kD = 0;
//     static double prev_error = 0, prev_I = 0;
//     static int gain = 100;
//     double p = 0, i = 0, d = 0, pid_value;

//     p = PIDValue;
//     i = prev_I;
//     d = p - prev_error;

//     pid_value = kP * p + kI * i + kD * d;
//     prev_error = p;
//     prev_I = i;

//     pid_value *= gain / 100;

//     constrain(pid_value, 0, INITIAL_SPEED);
//     return pid_value;
// }

void AutoPID::StopAllMotor()
{ // Idle the robot
    int temp[2] = {0};
    ShiftSpeed(temp);
}

void AutoPID::ShiftSpeed(int *MotorSpeed)
{                             // Shift the speed to the motors
    MotorMapping(MotorSpeed); // vut
    //  Serial.print(MotorSpeed[0]);
    //  Serial.print("  ");
    //  Serial.println(MotorSpeed[1]);
    for (int i = 0; i < 2; i++)
    {
        if (MotorSpeed[i] >= 0)
        {
            analogWrite(MotorInput[i], MotorSpeed[i]);
            digitalWrite(MotorOutput[i], LOW);
        }
        else
        {
            digitalWrite(MotorInput[i], LOW);
            analogWrite(MotorOutput[i], -MotorSpeed[i]);
        }
    }
}

void AutoPID::MotorMapping(int *MotorSpeed)
{
    int TEMP_INITIAL_SPEED = 0;
    // if (millis() - sys_start < 600)
    // {
    //     TEMP_INITIAL_SPEED = (float)(INITIAL_SPEED * ((millis() - sys_start)) / 600);
    // }
    // else
    // {
    TEMP_INITIAL_SPEED = INITIAL_SPEED;
    // }
    int maxx = MotorSpeed[0];
    maxx = (maxx < MotorSpeed[1]) ? MotorSpeed[1] : maxx;
    // gan cho maxx gia tri toc do cua banh nao lon hon
    if (maxx > TEMP_INITIAL_SPEED)
    {
        double ratio = (double)TEMP_INITIAL_SPEED / maxx;
        for (int i = 0; i < 2; i++)
        {
            MotorSpeed[i] *= ratio;
        }
    }
}

int AutoPID::GetError() // return value of P ~ error
{                       // Get the "error" in the moving direction
    static int prev_error = 0;
    switch (HighSignalCount())
    {
    case 0:
    {
        // CheckModeSwitch();`
        if (prev_error == 0)
        {
            return 0;
        }
        else if (prev_error == 4 || prev_error == 5)
        {
            prev_error = 5;
            return 5;
        }
        else if (prev_error == -4 || prev_error == -5)
        {
            prev_error = -5;
            return -5;
        }
        else
            return prev_error;
        break;
    }
    case 1:
    {
        for (int i = 0; i < 5; i++)
        {
            if (Line[i])
            {
                switch (i)
                {
                case 0:
                {
                    prev_error = -4;
                    return -4;
                    break;
                }
                case 1:
                {
                    prev_error = -2;
                    return -2;
                    break;
                }
                case 2:
                {
                    prev_error = 0;
                    return 0;
                    break;
                }
                case 3:
                {
                    prev_error = 2;
                    return 2;
                    break;
                }
                case 4:
                {
                    prev_error = 4;
                    return 4;
                    break;
                }
                default:
                {
                    return prev_error;
                    break;
                }
                }
                break;
            }
        }
        break;
    }
    case 2:
    {
        if (Line[0] && Line[1])
        {
            prev_error = -3;
            return -3;
        }
        // else if (Line[1] && Line[3])
        // {
        //   prev_error = -7;
        //   return -7;
        // }
        else if (Line[1] && Line[2])
        {
            prev_error = -1;
            return -1;
        }
        else if (Line[2] && Line[3])
        {
            prev_error = 1;
            return 1;
        }
        else if (Line[3] && Line[4])
        {
            prev_error = 3;
            return 3;
        }
        else
            return prev_error;
        break;
    }
    case 3:
    {
        if (Line[1] && Line[2] && Line[3])
        {
            prev_error = 0;
            return 0;
        }
        else if (Line[0] && Line[1] && Line[2])
        {
            prev_error = -1;
            return -1;
        }
        else if (Line[2] && Line[3] && Line[4])
        {
            prev_error = 1;
            return 1;
        }
        else
            return prev_error;
        break;
    }
    case 5:
    {
        prev_error = 0;
        return 0;
    }
    default:
    {

        return 0;
        break;
    }
    }
    return 0;
}

int AutoPID::HighSignalCount()
{ // Count the high signal that speed up the GetError function
    int count = 0;
    for (int i = 0; i < 5; i++)
    {
        if (Line[i])
        {
            count++;
        }
    }
    return count;
}
