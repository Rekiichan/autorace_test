#include "main.h"
#define __LINE_PROCESS__

class Line_Process
{
public:
  int GetError();
  int HighSignalCount();

  int GetError() // return value of P ~ error
  {              // Get the "error" in the moving direction
    static int prev_error = 0;
    switch (HighSignalCount())
    {
    case 0:
    {
      // CheckModeSwitch();
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
        prev_error = -3;
        return -3;
      }
      else if (Line[2] && Line[3] && Line[4])
      {
        prev_error = 3;
        return 3;
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
    return;
  }

  int HighSignalCount()
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
};
