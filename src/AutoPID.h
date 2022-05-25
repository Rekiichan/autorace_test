class AutoPID
{
public:
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
