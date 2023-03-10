#include "Radar.h"

Radar::Radar(int echo_pin, int trigger_pin, int servo_pin) :
echo_pin_(echo_pin),
trigger_pin_(trigger_pin),
servo_pin_(servo_pin)
{
}

// setting up the pins and the radar
void Radar::Setup()
{
    pinMode(trigger_pin_, OUTPUT);
    pinMode(echo_pin_, INPUT);
    servo_.attach(servo_pin_);
}

// Calculates the distance and returns true when there was an object in the accepted range, else false
bool Radar::CalculateDistance()
{
    digitalWrite(trigger_pin_, HIGH);
    delay(10);
    digitalWrite(trigger_pin_, LOW);
    long duration = pulseIn(echo_pin_, HIGH);
    distance_ = (duration / 2) * kSpeedOfSound;

    return IsDistanceInRange();
}

//Checks whether or not the distance is in range
bool Radar::IsDistanceInRange()
{
    return distance_ >= kMinDistance && distance_ <= kMaxDistance;
}

// Sets the angle of the servo
void Radar::SetAngle(int angle_in_degrees)
{
    servo_.write(angle_in_degrees);
}

// returns the last found distance
long Radar::GetDistance()
{
    return distance_;
}
