#include "main.h"
#define __LINE_TRACKING__

class Line_Tracking
{
public:
    Sensor_Reader SR;
    PID_Control PC;
    Motor_Control MC;

    void FollowLine()
    {                         // Main action for the robot to follow the line
        SR.GetSensorStatus(); // lay trang thai cua 5 sensor IR
        PC.LinePIDFilter();
        MC.ShiftSpeed(Motor);
    }
};
