#pragma once
#include <Wire.h>
#include "SensirionI2CScd4x.h"
#include "msgconst.hpp"

class Sensor {
    public:
        Sensor(void);
        void getSerials(uint16_t &serial0, uint16_t &serial1, uint16_t &serial2);
        void readData(uint16_t &co2, float &temp, float &humidity);

        bool isConfigured = false;
    private:
        void initialize();
        void printSerialNumber(uint16_t serial0, uint16_t serial1, uint16_t serial2);
        void printUint16Hex(uint16_t value);

        SensirionI2CScd4x scd4x;

        // Default I2C pins
        uint8_t scl_pin = 14;
        uint8_t sda_pin = 2;

       
        uint16_t error;
        char errorMessage[256];
      


};