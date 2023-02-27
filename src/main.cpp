#include <Arduino.h>
#include "config.h"
#include "Radar.h"

Radar myRadar(ECHO_PIN, TRIGGER_PIN, SERVO_PIN);
int angleInDegrees = 0;

void setup() {
    myRadar.Setup();
    myRadar.SetAngle(angleInDegrees);
}

void loop() {
    for (angleInDegrees = 180; angleInDegrees >= 0; angleInDegrees--) { // goes from 180 degrees to 0 degrees
    myRadar.SetAngle(angleInDegrees);
    Serial.println(angleInDegrees);
  }

  for (angleInDegrees = 0; angleInDegrees <= 180; angleInDegrees++) {   // goes from 0 degrees to 180 degrees
    myRadar.SetAngle(angleInDegrees);
    Serial.println(angleInDegrees);
  }
    
}
