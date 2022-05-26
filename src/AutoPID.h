#ifndef __AUTO_PID__
#define __AUTO_PID__
class AutoPID
{
public:
    // variable
    int Sensor_HIGH = 500; // High level for optical sensor
    int INITIAL_SPEED = 255;
    long long int sys_start = 0;

    // array
    static int MotorInput[2];
    static int MotorOutput[2];
    static int Sensors[5];
    static int Motor[2];
    static bool Line[5];

    //function
    void FollowLine();
    void GetSensorStatus();
    bool ReadLine(int index);
    void LinePIDFilter();
    double SpeedPIDFilter(double PIDValue);
    void StopAllMotor();
    void ShiftSpeed(int *MotorSpeed);
    void MotorMapping(int *MotorSpeed);
    int GetError();
    int HighSignalCount();
};
#endif
