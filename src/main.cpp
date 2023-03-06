#include <Arduino.h>
#include <IRremote.hpp>
#include "config.h"
#include "Radar.h"
#include "RadarDirection.h"
#include "RadarControlMode.h"
#include "InfraredRemoteCommands.h"

Radar myRadar(ECHO_PIN, TRIGGER_PIN, SERVO_PIN);
int angleInDegrees;
RadarDirection direction;
RadarControlMode controlMode;
IRrecv infraredRemote(8);

void setup() 
{
  angleInDegrees = 0;
  direction = RadarDirection::kRight;
  controlMode = RadarControlMode::kAutomatic;
  myRadar.Setup();
  myRadar.SetAngle(angleInDegrees);
  infraredRemote.start();
}

void loop() 
{
  if (infraredRemote.decode()) 
  {
    int command = infraredRemote.decodedIRData.command;

    if (command == InfraredRemoteCommands::kXButton) 
    {
      ChangeControlMode();
      infraredRemote.resume();
    }
  }

  if (controlMode == RadarControlMode::kAutomatic) 
  {
    HandleAutomatic();
  }
  else if (controlMode == RadarControlMode::kManual) 
  {
    HandleManual();
  }

  ClampAngle();
  myRadar.SetAngle(angleInDegrees);
  Serial.println(angleInDegrees);
}

void HandleAutomatic() 
{
  if (direction == RadarDirection::kRight) 
  {
    angleInDegrees++;
  }
  else if (direction == RadarDirection::kLeft) 
  {
    angleInDegrees--;
  }
}

void HandleManual() 
{
  if (infraredRemote.decode()) 
    {
      int command = infraredRemote.decodedIRData.command;
    
      if (command == InfraredRemoteCommands::kRightButton)
      {
        angleInDegrees += 10;
        infraredRemote.resume();
      }
      else if (command == InfraredRemoteCommands::kLeftButton)
      {
        angleInDegrees -= 10;
        infraredRemote.resume();
      }
    }
}

void ClampAngle() 
{
  if (angleInDegrees < Radar::kAngleMin)
  {
    angleInDegrees = Radar::kAngleMin;
    if (controlMode == RadarControlMode::kAutomatic) 
    {
      direction = RadarDirection::kRight;
    }
  }
  else if (angleInDegrees > Radar::kAngleMax) 
  {
    angleInDegrees = Radar::kAngleMax;
    if (controlMode == RadarControlMode::kAutomatic) 
    {
      direction = RadarDirection::kLeft;
    }
  }
}

void ChangeControlMode() 
{
  if (controlMode == RadarControlMode::kAutomatic) 
  {
    controlMode = RadarControlMode::kManual;
    return;
  }

  controlMode = RadarControlMode::kAutomatic;
}
