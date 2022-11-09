add_executable(sequencer) # CMAKE (target)

pico_generate_pio_header(sequencer ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio) # PICO SDK (PIO)

target_sources(sequencer PRIVATE sequencer.c neopixel.c) # CMAKE -> C (compiler)
target_link_libraries(sequencer PRIVATE pico_stdlib hardware_pio) # CMAKE -> C (linker)

pico_enable_stdio_usb(sequencer 1) # PICO SDK (USB)
pico_enable_stdio_uart(sequencer 0) # PICO SDK (USB)

pico_add_extra_outputs(sequencer) # PICO SDK (UF2)
