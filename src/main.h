#ifndef __ARDUINO__
#include <Arduino.h>
#endif

#define __ARDUINO__

#ifndef __MOTOR_CONTROL__
#include "Motor_Control.cpp"
#endif

#ifndef __LINE_PROCESS__
#include "Line_Process.cpp"
#endif

#ifndef __LINE_TRACKING__
#include "Line_Tracking.cpp"
#endif

#ifndef __PID_CONTROL__
#include "PID_Control.cpp"
#endif

#ifndef __SENSOR_READER__
#include "Sensor_Reader.cpp"
#endif

static int Sensor_HIGH = 500; // High level for optical sensor
static int INITIAL_SPEED = 255;

static const int MotorInput[2] = {10, 9};
static const int MotorOutput[2] = {11, 8};
static const int Sensors[5] = {A0, A1, A2, A3, A4};

static int Motor[2] = {0};
static bool Line[5] = {false};

static long long int sys_start = 0;
static int Mode = 0; // 0 for line tracking, 1 for sonar routing