#include "hardware/pio.h"
#include "ws2812.pio.h" 

#define PIO         pio0
#define SM          0
#define FREQ        800000
#define PIN         PICO_DEFAULT_WS2812_PIN
#define POWER_PIN   PICO_DEFAULT_WS2812_POWER_PIN
#define IS_RGBW     true  

void neopixel_init() {
    // power up WS2812 on Qt Py, using pin defs from board header file
    // pico-sdk/src/boards/include/boards/adafruit_qtpy_rp2040.h
    gpio_init(POWER_PIN);
    gpio_set_dir(POWER_PIN, GPIO_OUT);
    gpio_put(POWER_PIN, 1);

    // program PIO using helper function from ws2812.pio
    uint offset = pio_add_program(PIO, &ws2812_program);
    ws2812_program_init(PIO, SM, offset, PIN, FREQ, IS_RGBW);
}
           

void neopixel_set_rgb(uint32_t rgb) {
    // convert RGB to GRB
    uint32_t grb = ((rgb & 0xFF0000) >> 8) | ((rgb & 0x00FF00) << 8) | (rgb & 0x0000FF);
    pio_sm_put_blocking(pio0, 0, grb << 8u);
}

