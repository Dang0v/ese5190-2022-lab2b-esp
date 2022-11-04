add_executable(sequencer) # CMAKE (target)

target_sources(sequencer PRIVATE logic_analyser.c) # CMAKE -> C (compiler)
target_link_libraries(sequencer PRIVATE pico_stdlib hardware_pio hardware_dma) # CMAKE -> C (linker)

pico_enable_stdio_usb(sequencer 1) # PICO SDK (USB)
pico_enable_stdio_uart(sequencer 0) # PICO SDK (USB)

pico_add_extra_outputs(sequencer) # PICO SDK (UF2)
