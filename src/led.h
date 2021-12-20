#ifndef CO2_AMPEL_LED_H
#define CO2_AMPEL_LED_H

#include <FastLED.h>

#include "config.h"

class Led
{
private:
    CRGB leds[LEDS_NUM];
    void all(CRGB color);
public:
    static uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
        return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
    }

    void init();
    void drawRing(CRGB color);
    void drawGauge(uint16_t co2);
};
#endif