#include "sensor.hpp"

Sensor::Sensor(void) {
    initialize();
}

void Sensor::initialize() {
    if (isConfigured) {
        return;
    }

    Wire.begin(sda_pin, scl_pin); // If something is wrong, it is required to set address as well 0x62
    scd4x.begin(Wire);

    error = scd4x.stopPeriodicMeasurement();
    if (error) {
        Serial.print(ERR_STOP_PERIOD_MEAS);
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }

    error = scd4x.startPeriodicMeasurement();
    if (error) {
        Serial.print(ERR_START_PERIOD_MEAS);
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }

    Serial.println(WAITING_MEASUREMENT);

    if (!error) {
        isConfigured = true;
    }
}

void Sensor::getSerials(uint16_t &serial0, uint16_t &serial1, uint16_t &serial2) {
    if (!isConfigured) {
        return;
    }

    error = scd4x.getSerialNumber(serial0, serial1, serial2);
    if (error) {
        Serial.print(ERR_GETSERIAL);
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else {
        printSerialNumber(serial0, serial1, serial2);
    }
}

void Sensor::readData() {
    if (!isConfigured) {
        return;
    }
    
    co2 = 0;
    temp = 0.0f;
    humidity = 0.0f;

    bool isDataReady = false;
    error = scd4x.getDataReadyFlag(isDataReady);
    if (error) {
        Serial.print(ERR_GET_DATAS_READY);
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
        return;
    }
    if (!isDataReady) {
        return;
    }
    error = scd4x.readMeasurement(co2, temp, humidity);
    if (error) {
        Serial.print(ERR_READ_MEASUREMENT);
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else if (co2 == 0) {
        Serial.println(WARN_INVALID_CO2_SAMPLE);
    } else {
        Serial.print("Co2:");
        Serial.print(co2);
        Serial.print("\t");
        Serial.print("Temperature:");
        Serial.print(temp);
        Serial.print("\t");
        Serial.print("Humidity:");
        Serial.println(humidity);
    }
}

void Sensor::printSerialNumber(uint16_t serial0, uint16_t serial1, uint16_t serial2) {
    Serial.print("Serial: 0x");
    printUint16Hex(serial0);
    printUint16Hex(serial1);
    printUint16Hex(serial2);
    Serial.println();
}

void Sensor::printUint16Hex(uint16_t value) {
    Serial.print(value < 4096 ? "0" : "");
    Serial.print(value < 256 ? "0" : "");
    Serial.print(value < 16 ? "0" : "");
    Serial.print(value, HEX);
}

uint16_t Sensor::getCO2() {
    return co2;
}

float Sensor::getTemp() {
    return temp;
}

float Sensor::getHumidity() {
    return humidity;
}
