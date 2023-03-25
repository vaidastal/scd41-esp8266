#include <Arduino.h>
#include "sensor.hpp"

Sensor *scd41;

void setup() {

    Serial.begin(115200);
    while (!Serial) {
        delay(100);
    }

    scd41 = new Sensor();

}

void loop() {
   

    delay(100);

    // Read Measurement
    uint16_t co2 = 0;
    float temperature = 0.0f;
    float humidity = 0.0f;

    if (scd41->isConfigured) {
      scd41->readData(co2, temperature, humidity);
    } else {
      return;
    }
    
}