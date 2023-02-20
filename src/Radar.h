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
};