add_executable(register_repl) # CMAKE (target)

target_sources(register_repl PRIVATE register_repl.c) # CMAKE -> C (compiler)
target_link_libraries(register_repl PRIVATE pico_stdlib) # CMAKE -> C (linker)

pico_enable_stdio_usb(register_repl 1) # PICO SDK (USB)
pico_enable_stdio_uart(register_repl 0) # PICO SDK (USB)

pico_add_extra_outputs(register_repl) # PICO SDK (UF2)
