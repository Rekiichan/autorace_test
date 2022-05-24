#include "main.h"
#define __SENSOR_READER__

class Sensor_Reader
{
public:
    //define
    void GetSensorStatus();
    bool ReadLine(int index);

    //declare
    void GetSensorStatus()
    { // Get all the sensor status
        for (int i = 0; i < 5; i++)
        {
            Line[i] = ReadLine(i);
        }
    }

    bool ReadLine(int index)
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
};
