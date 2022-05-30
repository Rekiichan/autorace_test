#define Sensor_HIGH 500 // High level for optical sensor
int INITIAL_SPEED = 255;
int temp_speed = 160; // hieu chinh lai max speed trong ham motor mapping

double kP = 30;
double kI = 0;
double kD = 39;

#define trig 8
#define echo 9
const int MotorInput[2] = {
    10,
    6};
const int MotorOutput[2] = {
    11,
    7};
const int Sensors[5] = {
    A0,
    A1,
    A2,
    A3,
    A4};

int Motor[2] = {
    0};
bool Line[5] = {
    false};

void (*SystemReset)(void) = 0;
long long int sys_start = 0;

int checkBarrier();
bool ReadLine(int index);
void GetSensorStatus();
void LinePIDFilter();
void MotorMapping(int *MotorSpeed);
void ShiftSpeed(int *MotorSpeed);
int HighSignalCount();
int GetError();

void setup()
{
  for (int i = 0; i < 2; i++)
  {
    pinMode(MotorInput[i], OUTPUT);
    pinMode(MotorOutput[i], OUTPUT);
  }
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  for (int i = 0; i < 5; i++)
  {
    pinMode(Sensors[i], INPUT);
  }
  StopAllMotor();
  sys_start = millis();
  //   Serial.println("System started");
}

void loop()
{
  FollowLine();
}

void GetSensorStatus()
{ // Get all the sensor status
  for (int i = 0; i < 5; i++)
  {
    Line[i] = ReadLine(i);
  }
}

bool ReadLine(int index)
{ // Get the sensor status for each sensor
  int temp = analogRead(Sensors[index]);
  if (temp >= Sensor_HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int HighSignalCount()
{ // Count the high signal that speed up the GetError function
  int count = 0;
  for (int i = 0; i < 5; i++)
  {
    if (Line[i])
    {
      count++;
    }
  }
  return count;
}

void FollowLine()
{ // Main action for the robot to follow the line
  GetSensorStatus();
  LinePIDFilter();
  ShiftSpeed(Motor);
}

void StopAllMotor()
{ // Idle the robot
  int temp[2] = {
      0};
  ShiftSpeed(temp);
}

void LinePIDFilter()
{ // PID control in line tracking mode

  static double prev_error = 0, prev_I = 0;
  double p = 0, i = 0, d = 0, pid_value;

  p = GetError();
  i = prev_I + p;
  d = p - prev_error;

  pid_value = kP * p + kI * i + kD * d;
  prev_I = i;
  prev_error = p;
  Motor[0] = INITIAL_SPEED + pid_value; // trai
  Motor[1] = INITIAL_SPEED - pid_value; // phai
}

void ShiftSpeed(int *MotorSpeed)
{ // Shift the speed to the motors
  MotorMapping(MotorSpeed);
  for (int i = 0; i < 2; i++)
  {
    if (MotorSpeed[i] >= 0)
    {
      analogWrite(MotorInput[i], MotorSpeed[i]);
      digitalWrite(MotorOutput[i], LOW);
    }
    else
    {
      digitalWrite(MotorInput[i], LOW);
      analogWrite(MotorOutput[i], -MotorSpeed[i]);
    }
  }
}

void MotorMapping(int *MotorSpeed)
{
  int TEMP_INITIAL_SPEED = 0;
  if (millis() - sys_start < 600)
  {
    TEMP_INITIAL_SPEED = (float)(INITIAL_SPEED * ((millis() - sys_start)) / 600);
  }
  else
  {
    TEMP_INITIAL_SPEED = temp_speed;
  }
  int maxx = MotorSpeed[0];
  maxx = (maxx < MotorSpeed[1]) ? MotorSpeed[1] : maxx;
  if (maxx > TEMP_INITIAL_SPEED)
  {
    double ratio = (double)TEMP_INITIAL_SPEED / maxx;
    for (int i = 0; i < 2; i++)
    {
      MotorSpeed[i] *= ratio;
    }
  }
}

int GetError() // return value of P ~ error
{
  static int prev_error = 0;
  switch (HighSignalCount())
  {
  case 0:
    if (prev_error == 0)
    {
      return 0;
    }
    else if (prev_error == 4 || prev_error == 5)
    {
      prev_error = 5;
      return 5;
    }
    else if (prev_error == -4 || prev_error == -5)
    {
      prev_error = -5;
      return -5;
    }
    else
      return prev_error;
    break;

  case 1:
  {
    for (int i = 0; i < 5; i++)
    {
      if (Line[i])
      {
        switch (i)
        {
        case 0:
        {
          prev_error = -4;
          return -4;
          break;
        }
        case 1:
        {
          prev_error = -2;
          return -2;
          break;
        }
        case 2:
        {
          prev_error = 0;
          return 0;
          break;
        }
        case 3:
        {
          prev_error = 2;
          return 2;
          break;
        }
        case 4:
        {
          kP = 30;
          kD = 39;
          prev_error = 4;
          return 4;
          break;
        }
        default:
        {
          return prev_error;
          break;
        }
        } // sw
        break;
      } // if
    }   // for
    break;
  }
  case 2:
  {
    if (Line[0] && Line[1])
    {
      prev_error = -3;
      return -3;
    }
    else if (Line[1] && Line[2])
    {
      prev_error = -1;
      return -1;
    }
    else if (Line[2] && Line[3])
    {
      prev_error = 1;
      return 1;
    }
    else if (Line[3] && Line[4])
    {
      prev_error = 3;
      return 3;
    }
    else
      return prev_error;
    break;
  }
  case 3:
  {
    if (Line[1] && Line[2] && Line[3])
    {
      prev_error = 0;
      return 0;
    }
    else if (Line[0] && Line[1] && Line[2])
    {
      prev_error = -5;
      return -5;
    }
    else if (Line[2] && Line[3] && Line[4])
    {
      prev_error = 5;
      return 5;
    }
    else
      return prev_error;
    break;
  }
  case 5:
  {
    prev_error = 0;
    return 0;
  }
  default:
  {

    return 0;
    break;
  }
  }
  return prev_error;
}

int checkBarrier()
{
  unsigned long duration;
  int distance;
  digitalWrite(trig, 0);
  delayMicroseconds(2);
  digitalWrite(trig, 1);
  delayMicroseconds(5);
  digitalWrite(trig, 0);

  duration = pulseIn(echo, HIGH);
  distance = int(duration / 2 / 29.412);
  return distance;
}
