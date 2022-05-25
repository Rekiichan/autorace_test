#include "main.h"

AutoPID AP;

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
  AP.StopAllMotor();
  sys_start = millis();
  Serial.println("System started");
}

void loop()
{
  AP.FollowLine();
}
