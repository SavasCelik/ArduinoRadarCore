#include <Arduino.h>

class Radar {
    public:
    Radar(int echoPin, int triggerPin);
    void Setup();
    bool CalculateDistance();
    long GetDistance();

    private:
    int triggerPin;
    int echoPin;
    long distance = 0;
    int minDistance;
    int maxDistance;
    const double kSpeedOfSound = 0.03432; // speed of sound in centimeter/microseconds
};