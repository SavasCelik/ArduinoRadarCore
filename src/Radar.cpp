#include "Radar.h"

Radar::Radar(int echo_pin, int trigger_pin, int servo_pin) :
echo_pin_(echo_pin),
trigger_pin_(trigger_pin)
{
    servo_.attach(servo_pin);
    min_distance_ = 0;
    max_distance_ = 100;
}

void Radar::Setup()
{
    pinMode(trigger_pin_, OUTPUT);
    pinMode(echo_pin_, INPUT);
}

bool Radar::CalculateDistance()
{
    digitalWrite(trigger_pin_, HIGH);
    delay(10);
    digitalWrite(trigger_pin_, LOW);
    long duration = pulseIn(echo_pin_, HIGH);
    distance_ = (duration / 2) * kSpeedOfSound;

    return IsDistanceInRange();
}

void Radar::SetAngle(int angleInDegrees)
{
    servo_.write(angleInDegrees);
}

bool Radar::IsDistanceInRange()
{
    return distance_ >= min_distance_ && distance_ <= max_distance_;
}

long Radar::GetDistance()
{
    return distance_;
}
