#include "main.h"
#define __PID_CONTROL__

class PID_Control
{
public:
    Line_Process LP;
    void LinePIDFilter();
    double SpeedPIDFilter(double PIDValue);

    void LinePIDFilter()
    { // PID control in line tracking mode
        static double kP = 39, kI = 0.005, kD = 30;
        static double gain = 100;
        static double prev_error = 0, prev_I = 0;
        double p = 0, i = 0, d = 0, pid_value;

        p = LP.GetError(); // p thuc chat la error
        i = prev_I + p;
        d = p - prev_error;

        pid_value = kP * p + kI * i + kD * d;
        prev_I = i;
        prev_error = p;
        pid_value *= gain / 100;
        Motor[0] = INITIAL_SPEED + pid_value; // trai
        Motor[1] = INITIAL_SPEED - pid_value; // phai
    }

    double SpeedPIDFilter(double PIDValue) // Slow down or spped up the robot when necessary
    {
        static double kP = 0, kI = 0, kD = 0;
        static double prev_error = 0, prev_I = 0;
        static int gain = 100;
        double p = 0, i = 0, d = 0, pid_value;

        p = PIDValue;
        i = prev_I;
        d = p - prev_error;

        pid_value = kP * p + kI * i + kD * d;
        prev_error = p;
        prev_I = i;

        pid_value *= gain / 100;

        constrain(pid_value, 0, INITIAL_SPEED);
        return pid_value;
    }
};
