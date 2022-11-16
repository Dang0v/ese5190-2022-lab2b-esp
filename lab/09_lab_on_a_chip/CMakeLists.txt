add_executable(loc) # CMAKE (target)

pico_generate_pio_header(loc ${CMAKE_CURRENT_LIST_DIR}/i2c.pio)
pico_generate_pio_header(loc ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)

target_sources(loc PRIVATE
        loc.c
        pio_i2c.c
        pio_i2c.h
        APDS9960.c
        APDS9960.h
        neopixel.c
        neopixel.h
        )
target_link_libraries(loc PRIVATE pico_stdlib hardware_pio hardware_dma pico_multicore) # CMAKE -> C (linker)

pico_enable_stdio_usb(loc 1) # PICO SDK (USB)
pico_enable_stdio_uart(loc 0) # PICO SDK (USB)

pico_add_extra_outputs(loc) # PICO SDK (UF2)
