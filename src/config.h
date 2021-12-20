#include <FastLED.h>

#ifndef CO2_AMPEL_CONFIG_H
#define CO2_AMPEL_CONFIG_H

#define LEDS_PIN 13
#define LEDS_NUM 24
#define LEDS_BRIGHTNESS 25

#define LEDS_COLOR_INFO CRGB(0, 0, 255)
#define LEDS_COLOR_ERROR CRGB(255, 0, 0)
#define LEDS_COLOR_BAD CRGB(255, 0, 0)
#define LEDS_COLOR_OK CRGB(255, 255, 0)
#define LEDS_COLOR_GOOD CRGB(0, 255, 0)

#define NEW_GAUGE       // Farbgradient statt Punkte
#define BLINK 1600      // wenn definiert: LED Blinken 2x in LEDS_COLOR_BAD; wenn dieser Wert überschritten

#define OK 1000
#define BAD 2000
#define SCALE 100

#define UPDATE_INTERVAL 2500

#define SENSOR_SDA 21
#define SENSOR_SCL 22

//#define DISABLE_MQTT

#define WIFI_SSID "SSID"
#define WIFI_PASS "PASS"

#define MQTT_SERVER_IP "127.0.0.1"
#define MQTT_SERVER_PORT 999
#define MQTT_NAME "CO2-Ampel"

#define MAX_WIFI_TRIES 3
#define MAX_MQTT_TRIES 6

#define MQTT_TOPIC_CO2 "CO2/topic"
#define MQTT_TOPIC_TEMPERATURE "temperature/topic"
#define MQTT_TOPIC_HUMIDITY "humidity/topic"

#endif