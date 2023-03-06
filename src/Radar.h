#include <Arduino.h>
#include <Servo.h>

class Radar 
{
    public:
    Radar(int echo_pin, int trigger_pin, int servo_pin);
    void Setup();
    bool CalculateDistance();
    long GetDistance();
    void SetAngle(int angleInDegrees);
    
    private:
    bool IsDistanceInRange();

    public:
    static const int kAngleMin = 0;
    static const int kAngleMax = 180;

    private:
    Servo servo_;
    int echo_pin_;
    int trigger_pin_;
    long distance_;
    int min_distance_;
    int max_distance_;
    static const double kSpeedOfSound = 0.03432; // speed of sound in centimeter/microseconds
};
