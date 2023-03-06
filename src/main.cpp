#include <Arduino.h>
#include "config.h"
#include "Radar.h"
#include "RadarDirection.h"

Radar myRadar(ECHO_PIN, TRIGGER_PIN, SERVO_PIN);
int angleInDegrees;
RadarDirection direction;

void setup() 
{
  angleInDegrees = 0;
  direction = RadarDirection::kRight;
  myRadar.Setup();
  myRadar.SetAngle(angleInDegrees);
}

void loop() 
{
  if (direction == RadarDirection::kRight) 
  {
    angleInDegrees++;
  }
  else if (direction == RadarDirection::kLeft) 
  {
    angleInDegrees--;
  }

  if (direction != RadarDirection::kNone) 
  {
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

  myRadar.SetAngle(angleInDegrees);
  Serial.println(angleInDegrees);
}
