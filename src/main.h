#include "Motor_Control.h"
#include "Line_Process.h"
#include "Line_Tracking.h"
#include "PID_Control.h"
#include "Sensor_Reader.h"

static int Sensor_HIGH = 500; // High level for optical sensor
static int INITIAL_SPEED = 255;

static const int MotorInput[2] = {10, 9};
static const int MotorOutput[2] = {11, 8};
static const int Sensors[5] = {A0, A1, A2, A3, A4};

static int Motor[2] = {0};
static bool Line[5] = {false};

static long long int sys_start = 0;
static int Mode = 0; //0 for line tracking, 1 for sonar routing