### TODO:

You can now actually measure the timings you modeled in the last lab. Add APDS9960 support to your sensor, then set your system up to capture the following timing info:
- color packet delivered to PIO module
- bit delivered to WS2812 (24x/packet)
- full packet delivered to WS2812
- brightness changed on APDS

Run this experiment in both dark and light room settings (record initial ambient brightness in each case). The Neopixel should start 'off' and the ADPS9960 should be initialized with your preferred sampling rate (you may want to try a few different rates). Run the experiment for at least 100 samples at brightness settings of 0%, 25%, 50%, 75%, 100% (making sure to give the ADPS reading enough time to 'settle' each time Neopixel is turned off).

Report the observed 'jitter' based on misalignment with the free-running PWM module on the WS2012.

### COLOR packet delivered to PIO module

as shown in 06_pioscope

![image-20221115221201323](../06_pioscope/README.assets/image-20221115221201323.png)

![pio](README.assets/pio.png)

back to our code

```c
read_proximity(pio_2, sm, &proximity); //length = 1
read_rgbc(pio_2, sm, &r, &g, &b, &c);  //length = 6
sleep_ms(5);
```

A data package can be divided into four part

AB for proximity data, CD for ALS data.

![image-20221115222636599](README.assets/image-20221115222636599.png)

Here we can see, part A, C are write from master to slave, which announce that which register of slave will be read. And B, D will be the address and data. At dotted line is the repeated START bit, and at solid line is the stop bit.

### Packet send to WS2812

![image-20221115232936416](README.assets/image-20221115232936416.png)

![image-20221115233046181](README.assets/image-20221115233046181.png)

### DEMO

![image-20221115235207085](README.assets/image-20221115235207085.png)

![image-20221115235250507](README.assets/image-20221115235250507.png)

![image-20221115235259011](README.assets/image-20221115235259011.png)