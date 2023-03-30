#define OUTPUT_MSG_SIZE 512

//#pragma once

#include <Wire.h>
#include "SensirionI2CScd4x.h"
#include "msgconst.hpp"

class SCD41Sensor {
    public:
        bool isConfigured = false;

        SCD41Sensor(void);
        
        bool configureSensor();
        void getSerials(uint16_t &serial0, uint16_t &serial1, uint16_t &serial2);
        bool readData();
        uint16_t getCO2();
        float getTemp();
        float getHumidity();
        char getOutputMessage();
    private:
        SensirionI2CScd4x scd4x;

        // Default I2C pins
        uint8_t scl_pin = 14;
        uint8_t sda_pin = 2; 

        uint16_t co2;
        float temp;
        float humidity;
       
        char outputMessage[OUTPUT_MSG_SIZE];
        
        void printSerialNumber(uint16_t serial0, uint16_t serial1, uint16_t serial2);
        void printUint16Hex(uint16_t value);
};