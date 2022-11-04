### TODO:

- use your Lab 1 firefly code to generate ADPS9960 I2C traffic and display it on a lab oscilloscope
- take a screenshot of some portion of this exchange, and figure out/annotate what's happening based on the protocol documentation in the ADPS9960 datasheet 



### Test Result

First, we set the program request for r,g,b,c data. Then we can see the signal on oscilloscope that 4 data are sending at one time.

![676199688d60d6412b290e4bc5fe7d1](README.assets/676199688d60d6412b290e4bc5fe7d1.jpg)

![9247f31f6f457b32b3a8266ede09520](README.assets/9247f31f6f457b32b3a8266ede09520.jpg)



After zooming in, we can see how the 4 data are represented in the transmission process.

![685f74908eb6e7303758fe652cc96a4](README.assets/685f74908eb6e7303758fe652cc96a4.jpg)

![e57e4b7be9ce410c22001637978a7b6](README.assets/e57e4b7be9ce410c22001637978a7b6-1667596196816.jpg)

![7440594fbf085b0d6f692fbc57a25e5](README.assets/7440594fbf085b0d6f692fbc57a25e5.jpg)

![daee9b8bddd2fc33d42b64663a15554](README.assets/daee9b8bddd2fc33d42b64663a15554.jpg)



After we add a request for proximity, the data package became 5. (proximity + color)

![165edfaddc5665d0d25fc610d90fde6](README.assets/165edfaddc5665d0d25fc610d90fde6.jpg)



For gesture, package become 7. (gesture + color)

![20fa8854dbe1aea2c2caab13eb40a8c](README.assets/20fa8854dbe1aea2c2caab13eb40a8c.jpg)

