#include <SparkFun_SCD30_Arduino_Library.h>

class Sensor
{
private:
    SCD30 sensor;
    uint16_t co2;
    float temperature;
    float humidity;
public:
    bool init();
    void read();
    uint16_t getCo2();
    float getTemperature();
    float getHumidity();
};
