#include "scd4xsensor.hpp"

class DeviceState {
    public:
        bool isConfigured = false;
        
        static DeviceState &getInstance() {
           static DeviceState instance;                   
           return instance;
        }

        DeviceState(DeviceState const&) = delete;
        void operator=(DeviceState const&) = delete;

        void configureSensors();
        bool readSCD4xsensorData(void);
        uint16_t getCO2value(void);
        float getTempValue(void);
        float getHumidityValue(void);     
    private:
        SCD4xSensor *scd4x;              

        DeviceState() {};
};