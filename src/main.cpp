#include <Arduino.h>
#include "AutoPID.h"

int MotorInput[2] = {10, 9};
int MotorOutput[2] = {11, 8};
int Sensors[5] = {A0, A1, A2, A3, A4};

long long int sys_start = 0;

AutoPID PID;

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
  PID.StopAllMotor();
  sys_start = millis();
  Serial.println("System started");
}

void loop()
{
  PID.FollowLine();
}
