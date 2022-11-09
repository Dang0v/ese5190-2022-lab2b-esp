### TODO:

Toggle the Qt Py's Neopixel LED when the BOOT button is pressed, using only direct register reads to access the boot button status. You may use the SDK to initialize the board and the pins, and the WS2812 example code to toggle the Neopixel. 



### Explanation

In this part we should replace the function `gpio_get()` to direct register reading, the original code can be find in folder [code](https://github.com/ese-detkin-lab/ese5190-2022-lab2b-esp/tree/main/code)

```c
boot_pin_address = (uint32_t *) 0xd0000004;
full_gpio_register_value = (uint32_t) * boot_pin_address;
pin_21_selected_mask = 1ul << QTPY_BOOT_PIN;
pin_state= full_gpio_register_value & pin_21_selected_mask;
shifted_pin_state = pin_state >> QTPY_BOOT_PIN;
```

