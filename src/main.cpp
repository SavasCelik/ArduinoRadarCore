#include <Arduino.h>
#include <IRremote.hpp>
#include "config.h"
#include "Radar.h"
#include "RadarDirection.h"
#include "RadarControlMode.h"
#include "InfraredRemoteCommands.h"

Radar my_radar(ECHO_PIN, TRIGGER_PIN, SERVO_PIN);
int angle_in_degrees;
long distance;
RadarDirection direction;
RadarControlMode control_mode;
IRrecv infrared_remote(IREMOTE_PIN);
decode_results res;
int command2;

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
  command2 = -1;
  if (infrared_remote.decode()) 
  {
    command2 = infrared_remote.decodedIRData.command;
    infrared_remote.resume();
  }

  if (command2 == InfraredRemoteCommands::k5Button)
  {
    ChangeControlMode();
  }

  if (control_mode == RadarControlMode::kAutomatic) 
  {
    HandleAutomatic();
  }
  else if (control_mode == RadarControlMode::kManual) 
  {
    HandleManual();
  }

  ClampAngle();

  distance = -1;
  if (my_radar.CalculateDistance()) 
  {
    distance = my_radar.GetDistance();
  }
  delay(100);
  my_radar.SetAngle(angle_in_degrees);
  Serial.print(angle_in_degrees);
  Serial.print(";");
  Serial.println(distance);
}

void HandleAutomatic() 
{
  if (direction == RadarDirection::kRight) 
  {
    angle_in_degrees += 10;
  }
  else if (direction == RadarDirection::kLeft) 
  {
    angle_in_degrees -= 10;
  }
}

void HandleManual() 
{
  if (command2 == InfraredRemoteCommands::kRightButton)
  {
    angle_in_degrees -= 10;
  }
  else if (command2 == InfraredRemoteCommands::kLeftButton)
  {
    angle_in_degrees += 10;
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
