#include "main.h"

//define class
Line_Process lp;
Line_Tracking lt;
Motor_Control mc;
PID_Control pc;
Sensor_Reader sr;

void setup()
{
  for (int i = 0; i < 2; i++)
  {
    pinMode(MotorInput[i], OUTPUT);
    pinMode(MotorOutput[i], OUTPUT);
  }

  for (int i = 0; i < 5; i++)
  {
    pinMode(Sensors[i], INPUT);
  }
  Serial.begin(9600);
  mc.StopAllMotor();
  sys_start = millis();
  Serial.println("System started");
}

void loop()
{
  lt.FollowLine();
}

