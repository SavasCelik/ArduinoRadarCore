#include <Arduino.h>

class Radar {
    public:
    Radar(int echo_pin, int trigger_pin);
    void Setup();
    bool CalculateDistance();
    long GetDistance();
    
    private:
    bool IsDistanceInRange();

    private:
    int trigger_pin_;
    int echo_pin_;
    long distance_;
    int min_distance_;
    int max_distance_;
    const double kSpeedOfSound = 0.03432; // speed of sound in centimeter/microseconds
};