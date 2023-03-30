#include "scd41sensor.hpp"

class DeviceState {
    public:
        bool isConfigured = false;
        
        static DeviceState &getInstance() {
           static DeviceState instance;                   
           return instance;
        }

        DeviceState(DeviceState const&) = delete;
        void operator=(DeviceState const&) = delete;

        void initializeSensors();
        bool readSCD41sensorData(void);
        uint16_t getCO2value(void);
        float getTempValue(void);
        float getHumidityValue(void);     
    private:
        SCD41Sensor *scd41;              

        DeviceState() {};
};