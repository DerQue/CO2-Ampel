#include <Arduino.h>

#include "config.h"
#include "led.h"
#include "sensor.h"
#include "mqtt.h"

Led led;
Sensor sensor;
#ifndef DISABLE_MQTT
MQTT mqtt;
#endif

#ifdef BLINK
bool blink = false;
#endif

void setup() {
  Serial.begin(9600);
  Serial.println("CO² Ampel startet...");
  
  Serial.println("Leds startet...");
  led.init();
  led.drawRing(LEDS_COLOR_INFO);
  Serial.println("Leds einsatzbreit.");

  Serial.println("Sensor startet...");
  if(!sensor.init()) {
    while (1) {
      Serial.println("Keinen Sensor gefunden.");
      led.drawRing(LEDS_COLOR_ERROR);
      delay(2000);
      led.drawRing(CRGB::Black);
      delay(2000);
    }
  }
  Serial.println("Sensor einsatzbreit.");
}

void loop() {
  #ifndef DISABLE_MQTT
  mqtt.tick(led);
  #endif

  Serial.println("Hole Sensordaten...");
  sensor.read();

  Serial.print("CO²: ");
  Serial.print(sensor.getCo2());
  Serial.print(" ppm Temperatur: ");
  Serial.print(sensor.getTemperature());
  Serial.print(" °C Luftfeutigkeit: ");
  Serial.print(sensor.getHumidity());
  Serial.println("%");

  #ifndef DISABLE_MQTT
  mqtt.publish(MQTT_TOPIC_CO2, String(sensor.getCo2()).c_str());
  mqtt.publish(MQTT_TOPIC_TEMPERATURE, String(sensor.getCo2()).c_str());
  mqtt.publish(MQTT_TOPIC_HUMIDITY, String(sensor.getCo2()).c_str());
  #endif

  #ifdef BLINK
  if(sensor.getCo2() >= BLINK && !blink) {
    led.blink(sensor.getCo2());
    blink = true;
    delay(UPDATE_INTERVAL - 2000);
  } else {
    if(sensor.getCo2() < BLINK)
      blink = false;
  #endif
    led.drawGauge(sensor.getCo2());
    delay(UPDATE_INTERVAL);
  #ifdef BLINK
  }
  #endif
}