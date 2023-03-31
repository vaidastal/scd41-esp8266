#include "scd41sensor.hpp"

SCD4xSensor::SCD4xSensor(void) {
    
}

bool SCD4xSensor::configureSensor() {
    memset(&(outputMessage[0]), 0, (uint16_t) OUTPUT_MSG_SIZE);
    char messageBuffer[256];
    uint16_t error;
        
    if (isConfigured) {
        return isConfigured;
    }

    Wire.begin(sda_pin, scl_pin); // If something is wrong, it is required to set address as well 0x62
    scd4x.begin(Wire);

    error = scd4x.stopPeriodicMeasurement();
    if (error) {
        errorToString(error, messageBuffer, 256);
        sprintf(outputMessage, "%s %s", ERR_STOP_PERIOD_MEAS, messageBuffer);
    }

    error = scd4x.startPeriodicMeasurement();
    if (error) {
        errorToString(error, messageBuffer, 256);
        sprintf(outputMessage, "%s %s", ERR_START_PERIOD_MEAS, messageBuffer);
    }

    isConfigured = (!error) ? true : false;

    return isConfigured;
}

void SCD4xSensor::getSerials(uint16_t &serial0, uint16_t &serial1, uint16_t &serial2) {
    uint16_t error;

    if (!isConfigured) {
        return;
    }

    error = scd4x.getSerialNumber(serial0, serial1, serial2);
    if (error) {
        Serial.print(ERR_GETSERIAL);
        //errorToString(error, errorMessage, 256);
        //Serial.println(errorMessage);
    } else {
        printSerialNumber(serial0, serial1, serial2);
    }
}

bool SCD4xSensor::readData() {
    memset(&(outputMessage[0]), 0, (uint16_t) OUTPUT_MSG_SIZE);
    char messageBuffer[256];
    uint16_t error;
    co2 = 0;
    temp = 0.0f;
    humidity = 0.0f;


    if (!isConfigured) {
        sprintf(outputMessage, "%s", ERR_SENSOR_NOT_CONFIGURED);
        return false;
    }
    
    bool isDataReady = false;
    error = scd4x.getDataReadyFlag(isDataReady);
    if (error) {
        errorToString(error, messageBuffer, 256);
        sprintf(outputMessage, "%s %s", ERR_GET_DATAS_READY, messageBuffer);
        return false;
    }

    if (!isDataReady) {
        sprintf(outputMessage, "%s", WARN_DATA_NOT_READY);
        return false;
    }

    error = scd4x.readMeasurement(co2, temp, humidity);
    if (error) {
        errorToString(error, messageBuffer, 256);
        sprintf(outputMessage, "%s %s", ERR_READ_MEASUREMENT, messageBuffer);
        return false;
    } else if (co2 == 0) {
        sprintf(outputMessage, "%s", WARN_INVALID_CO2_SAMPLE);
        return false;
    } else {
        return true;
    }
    return false;
}

void SCD4xSensor::printSerialNumber(uint16_t serial0, uint16_t serial1, uint16_t serial2) {
    Serial.print("Serial: 0x");
    printUint16Hex(serial0);
    printUint16Hex(serial1);
    printUint16Hex(serial2);
    Serial.println();
}

void SCD4xSensor::printUint16Hex(uint16_t value) {
    Serial.print(value < 4096 ? "0" : "");
    Serial.print(value < 256 ? "0" : "");
    Serial.print(value < 16 ? "0" : "");
    Serial.print(value, HEX);
}

uint16_t SCD4xSensor::getCO2() {
    return co2;
}

float SCD4xSensor::getTemp() {
    return temp;
}

float SCD4xSensor::getHumidity() {
    return humidity;
}
