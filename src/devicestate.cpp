#include "devicestate.hpp"

void DeviceState::configureSensors() {
    scd4x = new SCD4xSensor();
    scd4x->configureSensor();
}

bool DeviceState::readSCD4xsensorData(void) {
    if (scd4x->isConfigured) {
      return scd4x->readSensorData();
    } else {
      return false;
    }
}

uint16_t DeviceState::getCO2value(void) {
    if (scd4x->isConfigured) {
        return scd4x->getCO2();
    } else {
        return 0;
    }
}

float DeviceState::getTempValue(void) {
    if (scd4x->isConfigured) {
        return scd4x->getTemp();
    } else {
        return 0;
    }
}

float DeviceState::getHumidityValue(void) {
    if (scd4x->isConfigured) {
        return scd4x->getHumidity();
    } else {
        return 0;
    }
}