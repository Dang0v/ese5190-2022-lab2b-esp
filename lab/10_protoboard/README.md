### TODO:

Add support for your custom circuit board to your sequencer, and give a demo.

### NOTE:

Since the APDS9960 drive is not running on another qtpy, we donnot need a circuit board. Connect the APDS9960 to qtpy by STEMMA is OK.

Multicore task is a convinience function for tasks running on the same time.

```c

void core1_main() {
    uint32_t proximity;
    uint32_t r, g, b, c;
    PIO pio_2 = pio1;
    uint sm = 0;
    while(true){
        read_proximity(pio_2, sm, &proximity);
        read_rgbc(pio_2, sm, &r, &g, &b, &c);
        //printf("proximity: %d   ",proximity);
        //printf("r:%d, g:%d, b:%d, c:%d\n", r, g, b, c);
    }
}

int main() {
    multicore_launch_core1(core1_main);
    main funtion
    ...
}

```