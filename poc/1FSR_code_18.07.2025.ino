#include <BluetoothSerial.h>
#include <esp_timer.h>  // High-resolution timer

BluetoothSerial SerialBT;

const int fsrPin = 34;     // GPIO34 (ADC1_CH6)
const int ledPin = 2;      // Onboard LED

volatile bool flag = false;
float meanValue = 0;
int minv;
int maxv;
int counter = 0;
int mean_samples= 100;  // no of sample before sending mean
int dt_sampling_mus = 1000;  // Sampling duratino in micro second

// Timer handle
esp_timer_handle_t periodic_timer;

// ==========================
// Function: updateStatistics
// ==========================
void updateStatisticsTask(void* arg) {
  int currValue = analogRead(fsrPin);

  if (counter <= 0) {
    meanValue = currValue;
    maxv = currValue;
    minv = currValue;
  } else if (counter > mean_samples) {
    counter = -1;
    flag = true;
  } else {
    meanValue = (meanValue * (counter + 1) + currValue) / (counter + 2);
    if (currValue > maxv) maxv = currValue;
    if (currValue < minv) minv = currValue;
  }
  counter++;
}

// ==========================
// Setup
// ==========================
void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);  // Boot indicator
  delay(1000);
  digitalWrite(ledPin, LOW);

  Serial.begin(115200);
  SerialBT.begin("ESP32");

  // Timer config
const esp_timer_create_args_t periodic_timer_args = {
  .callback = &updateStatisticsTask,
  .arg = NULL,
  .dispatch_method = ESP_TIMER_TASK,  // <-- this is correct
  .name = "sensor_timer"
};


  esp_timer_create(&periodic_timer_args, &periodic_timer);
  esp_timer_start_periodic(periodic_timer, dt_sampling_mus); // 1 ms = 1000 microseconds
}

// ==========================
// Main Loop
// ==========================
void loop() {
  if (flag) {
   Serial.print(minv);Serial.print(" ,"); 
   Serial.print(maxv); Serial.print(" ,"); 
   Serial.println(meanValue, 2);
    flag = false;
  }

  // Other background tasks can go here
}
