#include <BluetoothSerial.h>
#include <esp_timer.h>
#include "AnalogSensor.h"

int mean_samples= 100;  // no of sample before sending mean
int dt_sampling_mus = 1000;  // Sampling duratino in micro second

BluetoothSerial SerialBT;
AnalogSensor sensor1(34);
AnalogSensor sensor2(35);

// Timer callback
void updateSensors(void* arg) {
    sensor1.collectValue();
    sensor2.collectValue();
    // Add more sensors here if needed
}

void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32");

    // Configure and start timer
    const esp_timer_create_args_t timer_args = {
        .callback = &updateSensors,
        .arg = nullptr,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "sensor_timer"
    };

    esp_timer_handle_t timer;
    esp_timer_create(&timer_args, &timer);
    esp_timer_start_periodic(timer, 1000); // 1ms interval
}

void loop() {
    if (sensor1.isUpdated()) {
        Serial.print("Sensor1 - ");
        Serial.print("Min:"); Serial.print(sensor1.getMinValue());
        Serial.print(" Max:"); Serial.print(sensor1.getMaxValue());
        Serial.print(" Mean:"); Serial.println(sensor1.getMeanValue());
        sensor1.clearUpdatedFlag();
    }

    if (sensor2.isUpdated()) {
        Serial.print("Sensor2 - ");
        Serial.print("Min:"); Serial.print(sensor2.getMinValue());
        Serial.print(" Max:"); Serial.print(sensor2.getMaxValue());
        Serial.print(" Mean:"); Serial.println(sensor2.getMeanValue());
        sensor2.clearUpdatedFlag();
    }
    // delay(10);
}