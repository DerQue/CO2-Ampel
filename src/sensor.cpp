#include <Wire.h>
#include <SparkFun_SCD30_Arduino_Library.h>

#include "config.h"
#include "sensor.h"


bool Sensor::init() {
    Wire.begin(SENSOR_SDA, SENSOR_SCL);
    if (sensor.begin() == false)
    {
       return false;
    }
    return true;
}

void Sensor::read() {
    if(this->sensor.dataAvailable()) {
        this->co2 = sensor.getCO2();
        this->temperature = sensor.getTemperature();
        this->humidity = sensor.getHumidity();
    }
}

uint16_t Sensor::getCo2() {
    return this->co2;
}

float Sensor::getTemperature() {
    return this->temperature;
}

float Sensor::getHumidity() {
    return this->humidity;
}