# Continuous Sampling of an Analog Sensor

This is a repository for a simple example of code used to continuously sample an analog sensoer using a microcontroller (the code is developed for an esp32 but can be adapted for other platforms).

The aim of the code is to develop a class that can be used to sample an (noisy) analog sensor at regular intervals, and process the sample data, and provide accesss to processed (filtered) data. 

The code will collect values, and then processes them (average, filter, etc.) to provide a clean signal that can be used for further processing or display.

## Repository Structure

The reposisotory contains several self contained fodlers. 

- `poc`: proof of concept code that can be used to sample an analog sensor and print the values to the serial monitor.
- `oop_class_single`: a more structured approach using object-oriented programming to encapsulate the functionality of the sensor sampling.
- `oop_multifile`: an advanced version that uses multiple files to organize the code better, making it easier to maintain and extend.


# Future work

- `oop_class_with_interrupt`: an advanced version that uses interrupts to handle the sampling process, allowing for more efficient and responsive data collection.
- `oop_class_with_interrupt_and_queue`: the most advanced version that combines object-oriented programming, interrupts, and a queue to manage the sampled data efficiently.
- `oop_class_with_interrupt_and_queue_and_webserver`: the most advanced version that combines all previous features and adds a web server to serve the sampled data over HTTP.
- `oop_class_with_interrupt_and_queue_and_webserver_and_mqtt`: the ultimate version that integrates all previous features and adds MQTT support for real-time data publishing.
