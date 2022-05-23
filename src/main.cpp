#include <Arduino.h>
#include "main.h"

extern int Sensor_HIGH = 500; // High level for optical sensor
extern int INITIAL_SPEED = 255;

const int MotorInput[2] = {10, 9};
const int MotorOutput[2] = {11, 8};

const int Sensors[5] = {A0, A1, A2, A3, A4};

int Motor[2] = {0};
bool Line[5] = {false};

long long int sys_start = 0;
int Mode = 0; //0 for line tracking, 1 for sonar routing

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

