#include "AnalogSensor.h"

AnalogSensor::AnalogSensor(int pinNumber, int mean_samples) : 
    pin(pinNumber), meanValue(0), minv(0), maxv(0), counter(0), updated(false), storedmean(0), mean_samples(mean_samples){
    pinMode(pin, INPUT);
}

void AnalogSensor::collectValue() {
    int currValue = analogRead(pin);
    updateValues(currValue);
}

void AnalogSensor::updateValues(int currValue) {
    if (counter <= 0) {
        meanValue = currValue;
        maxv = currValue;
        minv = currValue;
    } else if (counter > mean_samples) {
        // when mean sample are collected then store the current mean value befor staring the 
        // next mean sample collection
        // the stored mean value is used when the mean sample is collected
        storedmean = meanValue;
        counter = -1;
        updated = true;
    } else {
        meanValue = (meanValue * (counter + 1) + currValue) / (counter + 2);
        if (currValue > maxv) maxv = currValue;
        if (currValue < minv) minv = currValue;
    }
    counter++;
}

float AnalogSensor::getMeanValue() const { return storedmean; }
int AnalogSensor::getMinValue() const { return minv; }
int AnalogSensor::getMaxValue() const { return maxv; }
bool AnalogSensor::isUpdated() const { return updated; }
void AnalogSensor::clearUpdatedFlag() { updated = false; }