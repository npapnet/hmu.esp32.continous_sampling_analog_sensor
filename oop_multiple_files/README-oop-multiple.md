# oop class - Multiple file

This is a simple example of how to use object-oriented programming in using multiple files to encapsulate the functionality of sampling an analog sensor using a microcontroller (the code is developed for an esp32 but can be adapted for other platforms).

## Features

- Enables Reading multiple analog pins simultaneously without too much boiler late
- Each sensor tracks mean, min, and max values
- Single hardware timer drives all sensors
- Simple API for checking values
- Bluetooth support included (optional)

## Basic Usage

```cpp
#include "AnalogSensor.h"

AnalogSensor sensor1(34);  // GPIO34
AnalogSensor sensor2(35);  // GPIO35

void setup() {
    Serial.begin(115200);
    initSensorTimer();  // Starts sampling
}

void loop() {
    if (sensor1.isUpdated()) {
        Serial.print("Min:"); Serial.print(sensor1.getMinValue());
        Serial.print(" Max:"); Serial.print(sensor1.getMaxValue());
        Serial.print(" Mean:"); Serial.println(sensor1.getMeanValue());
        sensor1.clearUpdatedFlag();
    }
}


## Class Methods

- AnalogSensor(pin): Constructor
- collectValue(): Takes new reading (called automatically)
- getMeanValue(): Returns rolling average
- getMinValue(): Returns minimum observed
- getMaxValue(): Returns maximum observed
- isUpdated(): Check if new stats available
- clearUpdatedFlag(): Reset update status

## Configuration

- Adjust dt_sampling_mus for sampling rate
- Modify mean_samples for statistics window size
- Add sensors for each analog pin needed

## Requirements
- ESP32 board
- Arduino-ESP32 core
- BluetoothSerial (optional)

## Installation

Copy AnalogSensor.h to your project

Include in main sketch

Create sensor instances