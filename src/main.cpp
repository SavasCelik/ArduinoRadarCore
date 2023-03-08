#include <Arduino.h>
#include <IRremote.hpp>
#include "config.h"
#include "Radar.h"
#include "RadarDirection.h"
#include "RadarControlMode.h"
#include "InfraredRemoteCommands.h"

Radar my_radar(ECHO_PIN, TRIGGER_PIN, SERVO_PIN);
int angle_in_degrees;
RadarDirection direction;
RadarControlMode control_mode;
IRrecv infrared_remote(IREMOTE_PIN);

// Predefined methods
void HandleAutomatic();
void HandleManual();
void ClampAngle();
void ChangeControlMode();

void setup() 
{
  Serial.begin(9600);
  angle_in_degrees = 0;
  direction = RadarDirection::kRight;
  control_mode = RadarControlMode::kManual;
  my_radar.Setup();
  my_radar.SetAngle(angle_in_degrees);
  infrared_remote.start();
}

void loop() 
{
  if (infrared_remote.decode()) 
  {
    int command = infrared_remote.decodedIRData.command;

    if (command == InfraredRemoteCommands::k5Button) 
    {
      ChangeControlMode();
      delay(100);
    }
    
    if (control_mode == RadarControlMode::kAutomatic)
    {
      infrared_remote.resume();
    }
  }

  if (control_mode == RadarControlMode::kAutomatic) 
  {
    HandleAutomatic();
    delay(25);
  }
  else if (control_mode == RadarControlMode::kManual) 
  {
    HandleManual();
  }

  ClampAngle();
  my_radar.SetAngle(angle_in_degrees);
  Serial.println(angle_in_degrees);
}

void HandleAutomatic() 
{
  if (direction == RadarDirection::kRight) 
  {
    angle_in_degrees++;
  }
  else if (direction == RadarDirection::kLeft) 
  {
    angle_in_degrees--;
  }
}

void HandleManual() 
{
  if (infrared_remote.decode()) 
  {
    infrared_remote.resume();
    int command = infrared_remote.decodedIRData.command;
    
    if (command == InfraredRemoteCommands::kRightButton)
    {
      angle_in_degrees -= 10;
    }
    else if (command == InfraredRemoteCommands::kLeftButton)
    {
      angle_in_degrees += 10;
    }
  }
}

void ClampAngle() 
{
  if (angle_in_degrees < Radar::kAngleMin)
  {
    angle_in_degrees = Radar::kAngleMin;
    if (control_mode == RadarControlMode::kAutomatic) 
    {
      direction = RadarDirection::kRight;
    }
  }
  else if (angle_in_degrees > Radar::kAngleMax) 
  {
    angle_in_degrees = Radar::kAngleMax;
    if (control_mode == RadarControlMode::kAutomatic) 
    {
      direction = RadarDirection::kLeft;
    }
  }
}

void ChangeControlMode() 
{
  if (control_mode == RadarControlMode::kAutomatic) 
  {
    control_mode = RadarControlMode::kManual;
    return;
  }

  control_mode = RadarControlMode::kAutomatic;
}
