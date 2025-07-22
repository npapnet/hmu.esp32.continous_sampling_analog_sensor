#include <BluetoothSerial.h>
#include <esp_timer.h>

BluetoothSerial SerialBT;

class AnalogSensor {
    private:
        int pin;
        float meanValue;
        int minv;
        int maxv;
        int counter;
        int mean_samples;
        bool updated;
        float storedmean;

    public:
        AnalogSensor(int pinNumber, int mean_samples) : pin(pinNumber), meanValue(0), minv(0), maxv(0), counter(0), updated(false), storedmean(0), mean_samples(mean_samples) {
            /* Initialize the pin as an input.
               This assumes the pin is capable of analog reading.
               For ESP32, pins 34-39 are typically used for analog input.
               Adjust according to your specific microcontroller's capabilities.
            */
            pinMode(pin, INPUT);
        }

        void collectValue() {
            // Read the current value from the analog pin
            // This assumes the pin is set up for analog input.
            // For ESP32, you can use analogRead(pin) to get the value.

            int currValue = analogRead(pin);
            updateValues(currValue);
        }

        void updateValues(int currValue) {
            // Update the mean, min, and max values

            if (counter <= 0) {
                meanValue = currValue;
                maxv = currValue;
                minv = currValue;
            } else if (counter > mean_samples) {
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

        float getMeanValue() const { return storedmean; }
        int getMinValue() const { return minv; }
        int getMaxValue() const { return maxv; }
        bool isUpdated() const { return updated; }
        void clearUpdatedFlag() { updated = false; }
};

// Global timer callback handler
void timerCallback(void* arg) {
    // Cast the argument back to our sensor array
    AnalogSensor** sensors = (AnalogSensor**)arg;
    
    // Update all sensors
    for (int i = 0; sensors[i] != nullptr; i++) {
        sensors[i]->collectValue();
    }
}

// ==========================
// Setup with sensor management
// ==========================
void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32");

    // Create your sensors (null-terminated array)
    static AnalogSensor* sensors[] = {
        new AnalogSensor(34),  // First sensor
        new AnalogSensor(35),  // Second sensor
        nullptr  // Marks end of array
    };

    // Timer config - pass the sensors array as argument
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &timerCallback,
        .arg = sensors,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "sensor_timer"
    };

    esp_timer_handle_t periodic_timer;
    esp_timer_create(&periodic_timer_args, &periodic_timer);
    esp_timer_start_periodic(periodic_timer, 1000); // 1ms
}

// ==========================
// Main Loop
// ==========================
void loop() {
    // You would need to make sensors accessible here, perhaps by declaring
    // them at a higher scope or using another method to track them
    
    // Example check (would need actual sensor references):
    /*
    if (sensor1.isUpdated()) {
        Serial.print("Min:"); Serial.print(sensor1.getMinValue());
        Serial.print(" Max:"); Serial.print(sensor1.getMaxValue());
        Serial.print(" Mean:"); Serial.println(sensor1.getMeanValue());
        sensor1.clearUpdatedFlag();
    }
    */
}