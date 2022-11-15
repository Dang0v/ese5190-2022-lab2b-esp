add_executable(APDS9960_pio)

pico_generate_pio_header(APDS9960_pio ${CMAKE_CURRENT_LIST_DIR}/i2c.pio)

target_sources(APDS9960_pio PRIVATE
        pio_i2c.c
        pio_i2c.h
        APDS9960.c
        APDS9960.h
        )

pico_enable_stdio_usb(APDS9960_pio 1) # PICO SDK (USB)
pico_enable_stdio_uart(APDS9960_pio 0) # PICO SDK (USB)

target_link_libraries(APDS9960_pio PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(APDS9960_pio)


