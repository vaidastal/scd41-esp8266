#include "state.hpp"

void DeviceState::configureSensors() {
    scd41 = new SCD4xSensor();
    scd41->configureSensor();
}

bool DeviceState::readSCD4xsensorData(void) {
    if (scd41->isConfigured) {
      return scd41->readSensorData();
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