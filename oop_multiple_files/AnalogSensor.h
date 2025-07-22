#ifndef ANALOG_SENSOR_H
#define ANALOG_SENSOR_H

#include <Arduino.h>

class AnalogSensor {
private:
    int pin;
    float meanValue;
    float storedmean;
    int minv;
    int maxv;
    int counter;
    int mean_samples;
    bool updated;

    void updateValues(int currValue);

public:
    AnalogSensor(int pinNumber, int mean_samples);
    void collectValue();
    float getMeanValue() const;
    int getMinValue() const;
    int getMaxValue() const;
    bool isUpdated() const;
    void clearUpdatedFlag();
};

#endif