#include <Arduino.h>
#include "config.h"
#include "Radar.h"
#include "RadarDirection.h"
#include "RadarControlMode.h"

Radar myRadar(ECHO_PIN, TRIGGER_PIN, SERVO_PIN);
int angleInDegrees;
RadarDirection direction;
RadarControlMode controlMode;

void setup() 
{
  angleInDegrees = 0;
  direction = RadarDirection::kRight;
  controlMode = RadarControlMode::kAutomatic;
  myRadar.Setup();
  myRadar.SetAngle(angleInDegrees);
}

void loop() 
{
  if (controlMode == RadarControlMode::kAutomatic) 
  {
    if (direction == RadarDirection::kRight) 
    {
      angleInDegrees++;
    }
    else if (direction == RadarDirection::kLeft) 
    {
      angleInDegrees--;
    }

    if (angleInDegrees < 0) 
    {
      angleInDegrees = 0;
      direction = RadarDirection::kRight;
    }
    else if (angleInDegrees > 180) 
    {
      angleInDegrees = 180;
      direction = RadarDirection::kLeft;
    }
  }
  else if (controlMode == RadarControlMode::kManual) 
  {
    //TODO: IRControl code here...
  }
  

  myRadar.SetAngle(angleInDegrees);
  Serial.println(angleInDegrees);
}
