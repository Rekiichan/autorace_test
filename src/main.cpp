#include <Arduino.h>
#include "main.h"

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
  StopAllMotor();
  sys_start = millis();
  Serial.println("System started");
}

void loop()
{
  FollowLine();
}

