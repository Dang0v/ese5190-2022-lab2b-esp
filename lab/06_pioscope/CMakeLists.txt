add_executable(pioscope) # CMAKE (target)

target_sources(pioscope PRIVATE logic_analyser.c) # CMAKE -> C (compiler)
target_link_libraries(pioscope PRIVATE pico_stdlib hardware_pio hardware_dma) # CMAKE -> C (linker)

pico_enable_stdio_usb(pioscope 1) # PICO SDK (USB)
pico_enable_stdio_uart(pioscope 0) # PICO SDK (USB)

pico_add_extra_outputs(pioscope) # PICO SDK (UF2)
