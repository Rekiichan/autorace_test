#include <Arduino.h>
#include "Line_Tracking.h"

void FollowLine()
{                      // Main action for the robot to follow the line
    GetSensorStatus(); // lay trang thai cua 5 sensor IR
    LinePIDFilter();
    ShiftSpeed(Motor);
}

int GetError()
{ // Get the "error" in the moving direction
    static int prev_error = 0;
    switch (HighSignalCount())
    {
    case 0:
    {
        CheckModeSwitch();
        if (prev_error == 0)
        {
            return 0;
        }
        else if (prev_error == 6 || prev_error == 7)
        {
            prev_error = 7;
            return 7;
        }
        else if (prev_error == -6 || prev_error == -7)
        {
            prev_error = -7;
            return -7;
        }
        else
            return prev_error;
        break;
    }
    case 1:
    {
        for (int i = 0; i < 7; i++)
        {
            if (Line[i])
            {
                switch (i)
                {
                case 0:
                {
                    prev_error = -6;
                    return -6;
                    break;
                }
                case 1:
                {
                    prev_error = -4;
                    return -4;
                    break;
                }
                case 2:
                {
                    prev_error = -2;
                    return -2;
                    break;
                }
                case 3:
                {
                    prev_error = 0;
                    return 0;
                    break;
                }
                case 4:
                {
                    prev_error = 2;
                    return 2;
                    break;
                }
                case 5:
                {
                    prev_error = 4;
                    return 4;
                    break;
                }
                case 6:
                {
                    prev_error = 6;
                    return 6;
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
            prev_error = -5;
            return -5;
        }
        else if (Line[1] && Line[3])
        {
            prev_error = -7;
            return -7;
        }
        else if (Line[1] && Line[2])
        {
            prev_error = -3;
            return -3;
        }
        else if (Line[2] && Line[3])
        {
            prev_error = -1;
            return -1;
        }
        else if (Line[3] && Line[4])
        {
            prev_error = 1;
            return 1;
        }
        else if (Line[4] && Line[5])
        {
            prev_error = 3;
            return 3;
        }
        else if (Line[5] && Line[3])
        {
            prev_error = 7;
            return 7;
        }
        else if (Line[5] && Line[6])
        {
            prev_error = 5;
            return 5;
        }
        else
            return prev_error;
        break;
    }
    case 3:
    {
        if (Line[1] && Line[2] && Line[3])
        {
            switch (-1)
            {
            case 0:
            {
                prev_error = 0;
                return 0;
            }
            case -1:
            case 1:
            {
                prev_error = -4;
                return -4;
            }
            }
        }
        else if (Line[0] && Line[1] && Line[2])
        {
            prev_error = -6;
            return -6;
        }
        else if (Line[3] && Line[4] && Line[5])
        {
            switch (1)
            {
            case 0:
            {
                prev_error = 0;
                return 0;
            }
            case 1:
            case -1:
            {
                prev_error = 4;
                return 4;
            }
            }
        }
        else if (Line[4] && Line[5] && Line[6])
        {
            prev_error = 6;
            return 6;
        }
        else if (Line[2] && Line[3] && Line[4])
        {
            prev_error = 0;
            return 0;
        }
        else
            return prev_error;
        break;
    }
    case 4:
    {
        if (Line[0] && Line[1] && Line[2] && Line[3])
        {
            switch (CheckBarrie(-1))
            {
            case 0:
            {
                prev_error = 0;
                return 0;
            }
            case -1:
            case 1:
            {
                prev_error = -8;
                return -8;
            }
            }
        }
        else if (Line[6] && Line[5] && Line[4] && Line[3])
        {
            switch (CheckBarrie(1))
            {
            case 0:
            {
                prev_error = 0;
                return 0;
            }
            case 1:
            case -1:
            {
                prev_error = 8;
                return 8;
            }
            }
        }
        else
        {
            return prev_error;
        }
        break;
    }
    case 5:
    {
        if (Line[0] && Line[1] && Line[2] && Line[3] && Line[4])
        {
            prev_error = -2;
            return -2;
        }
        else if (Line[1] && Line[2] && Line[3] && Line[4] && Line[5])
        {
            prev_error = 0;
            return 0;
        }
        else if (Line[2] && Line[3] && Line[4] && Line[5] && Line[6])
        {
            prev_error = 2;
            return 2;
        }
    }
    case 6:
    {
        if (Line[0] && Line[1] && Line[2] && Line[3] && Line[4] && Line[5])
        {
            prev_error = -1;
            return -1;
        }
        else if (Line[1] && Line[2] && Line[3] && Line[4] && Line[5] && Line[6])
        {
            prev_error = 1;
            return 1;
        }
    }
    case 7:
    {
        prev_error = 0;
        return 0;
    }
    default:
    {
        /*int temp = CountLeft() - CountRight();
          if (temp < -1) {
          prev_error = 8;
          return 8;
          } else if (temp > 1) {
          prev_error = -8;
          return -8;
          } else*/
        return 0;
        break;
    }
    }
}
