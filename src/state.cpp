#include "state.hpp"

void DeviceState::initializeSensors() {
    scd41 = new SCD41Sensor();
    scd41->configureSensor();
}

bool DeviceState::readSCD41sensorData(void) {
    if (scd41->isConfigured) {
      return scd41->readData();
    } else {
      return false;
    }
}

uint16_t DeviceState::getCO2value(void) {
    if (scd41->isConfigured) {
        return scd41->getCO2();
    } else {
        return 0;
    }
}

float DeviceState::getTempValue(void) {
    if (scd41->isConfigured) {
        return scd41->getTemp();
    } else {
        return 0;
    }
}

float DeviceState::getHumidityValue(void) {
    if (scd41->isConfigured) {
        return scd41->getHumidity();
    } else {
        return 0;
    }
}