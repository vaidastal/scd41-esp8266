#include <Arduino.h>
#include "WiFiSettings.h"
#include "LittleFS.h"
#include "state.hpp"

//Sensor *scd41;

void setup() {

    Serial.begin(115200);
    while (!Serial) {
        delay(100);
    }

    //scd41 = new Sensor();

    //LittleFS.begin();
    //LittleFS.begin();

    //WiFiSettings.connect();
}

void loop() {
   

    delay(100);
    //Serial.println("Status:" + DeviceState::getInstance().scd41->isConfigured);
    if (DeviceState::getInstance().readSCD41sensorData()) {
      Serial.print("CO2: "); Serial.println(DeviceState::getInstance().getCO2value());
    }

    // Read Measurement
    //uint16_t co2 = 0;
    //float temperature = 0.0f;
    //float humidity = 0.0f;

    //if (scd41->isConfigured) {
      //scd41->readData(co2, temperature, humidity);
    //} else {
    //  return;
    //}
    
}