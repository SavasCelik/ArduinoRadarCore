#include "Radar.h"

Radar::Radar(int echoPin, int triggerPin) :
echoPin(echoPin),
triggerPin(triggerPin)
{
    minDistance = 0;
    maxDistance = 100;
}

void Radar::Setup()
{
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

bool Radar::CalculateDistance()
{
    digitalWrite(triggerPin, HIGH);
    delay(10);
    digitalWrite(triggerPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) * 0.03432;

    return distance >= minDistance && distance <= maxDistance;
}

long Radar::GetDistance()
{
    return distance;
}
