add_executable(piosequencer) # CMAKE (target)

pico_generate_pio_header(piosequencer ${CMAKE_CURRENT_LIST_DIR}/i2c.pio)

target_sources(piosequencer PRIVATE
        piosequencer.c
        pio_i2c.c
        pio_i2c.h
        APDS9960.c
        APDS9960.h
        )
target_link_libraries(piosequencer PRIVATE pico_stdlib hardware_pio hardware_dma pico_multicore) # CMAKE -> C (linker)

pico_enable_stdio_usb(piosequencer 1) # PICO SDK (USB)
pico_enable_stdio_uart(piosequencer 0) # PICO SDK (USB)

pico_add_extra_outputs(piosequencer) # PICO SDK (UF2)
