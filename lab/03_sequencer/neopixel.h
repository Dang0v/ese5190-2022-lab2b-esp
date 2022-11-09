#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#define POWER_PIN   PICO_DEFAULT_WS2812_POWER_PIN

void neopixel_init();
void neopixel_set_rgb(uint32_t rgb);

#endif
