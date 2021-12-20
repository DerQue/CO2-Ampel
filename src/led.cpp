#include <FastLED.h>

#include "config.h"
#include "led.h"

void Led::all(CRGB color) {
    for (int i = 0; i < LEDS_NUM; ++i) {
        this->leds[i] = color;
    }
}

void Led::init()
{
    FastLED.addLeds<NEOPIXEL, LEDS_PIN>(this->leds, LEDS_NUM);
    FastLED.setBrightness(LEDS_BRIGHTNESS);
}

void Led::drawRing(CRGB color)
{
    this->all(color);
    FastLED.show();
}

void Led::drawGauge(uint16_t co2) {
    this->all(CRGB::Black);
    CRGB color;
    #ifdef NEW_GAUGE
        float percent = (float) co2 / BAD;
        if(percent > 1) percent = 1.0;
        color = CRGB(255 * percent, -255 * percent + 255, 0);
    #elif
        if(co2 >= BAD) {
            color = LEDS_COLOR_BAD;
        } else if (co2 >= OK) {
            color = LEDS_COLOR_OK;
        } else {
            color = LEDS_COLOR_GOOD;
        }
    #endif

    int numbersOfLeds = co2 / SCALE;
    if(numbersOfLeds > LEDS_NUM) numbersOfLeds = LEDS_NUM;

    for (int i = 0; i < numbersOfLeds; ++i) {
        this->leds[i] = color;
    }
    FastLED.show();
}