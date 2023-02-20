#include <Arduino.h>

class Radar {
    public:
    Radar(int echoPin, int triggerPin);
    void Setup();
    void CalculateDistance();
    long GetDistance();

    private:
    int triggerPin;
    int echoPin;
    long dauer = 0;
    long entfernung = 0;
};