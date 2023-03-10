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
int command;

/*** Predefined functions ***/
void HandleAutomatic();
void HandleManual();
void ClampAngle();
void ChangeControlMode();


// setting up the projekt
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

// looping over instructions
void loop() 
{
  command = -1;
  if (infrared_remote.decode()) 
  {
    command = infrared_remote.decodedIRData.command;
    infrared_remote.resume();
  }

  if (command == InfraredRemoteCommands::k5Button)
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

  my_radar.SetAngle(angle_in_degrees);
  
  distance = -1;
  if (my_radar.CalculateDistance()) 
  {
    distance = my_radar.GetDistance();
  }

  ClampAngle();
  Serial.print(angle_in_degrees);
  Serial.print(";");
  Serial.println(distance);
  delay(100);
}

// Handles the movement of the radar Automatically
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

// Handles the movement of the radar when a button was pressed
void HandleManual() 
{
  if (command == InfraredRemoteCommands::kRightButton)
  {
    angle_in_degrees -= 10;
  }
  else if (command == InfraredRemoteCommands::kLeftButton)
  {
    angle_in_degrees += 10;
  }
}

// guarantees that the radar doesent have unexpected angles 
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

// changes the control mode
void ChangeControlMode() 
{
  if (control_mode == RadarControlMode::kAutomatic) 
  {
    control_mode = RadarControlMode::kManual;
    return;
  }

  control_mode = RadarControlMode::kAutomatic;
}
