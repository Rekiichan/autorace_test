#include <Arduino.h>
#include "Line_Tracking.h"
#include "main.h"

void FollowLine()
{                      // Main action for the robot to follow the line
    GetSensorStatus(); // lay trang thai cua 5 sensor IR
    LinePIDFilter();
    ShiftSpeed(Motor);
}
