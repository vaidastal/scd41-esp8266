#include <Wire.h>
#include "SensirionI2CScd4x.h"
#include "parameters.hpp"

class SCD4xSensor {
    public:
        bool isConfigured = false;

        SCD4xSensor(void);
        
        bool configureSensor();
        void getSerials(uint16_t &serial0, uint16_t &serial1, uint16_t &serial2);
        bool readSensorData();
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
       
        char outputMessage[SENSOR_OUTPUT_MSG_SIZE];
        
        void printSerialNumber(uint16_t serial0, uint16_t serial1, uint16_t serial2);
        void printUint16Hex(uint16_t value);
};