#include "Motor_Control.h"
#include "Line_Process.h"
#include "Line_Tracking.h"
#include "PID_Control.h"
#include "Sensor_Reader.h"

#define Sensor_HIGH 500 // High level for optical sensor
int INITIAL_SPEED = 255;

const int MotorInput[2] = {10, 9};
const int MotorOutput[2] = {11, 8};

const int Sensors[5] = {A0, A1, A2, A3, A4};

int Motor[2] = {0};
bool Line[5] = {false};
