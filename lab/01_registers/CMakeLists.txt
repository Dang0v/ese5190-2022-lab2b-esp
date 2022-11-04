add_executable(flashlight_reg) # CMAKE (target)

pico_generate_pio_header(flashlight_reg ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio) # PICO SDK (PIO)

target_sources(flashlight_reg PRIVATE flashlight_reg.c neopixel.c) # CMAKE -> C (compiler)
target_link_libraries(flashlight_reg PRIVATE pico_stdlib hardware_pio) # CMAKE -> C (linker)



pico_enable_stdio_usb(flashlight_reg 1) # PICO SDK (USB)
pico_enable_stdio_uart(flashlight_reg 0) # PICO SDK (USB)

pico_add_extra_outputs(flashlight_reg) # PICO SDK (UF2)
