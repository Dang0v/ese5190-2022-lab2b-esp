#include "pico/stdlib.h"
#include <stdio.h>
#include "stdint.h"
#include "stdbool.h"
#include "hardware/gpio.h"
#include "registers.h"

typedef struct {
    ADDRESS addr;
    VALUE value;
    bool read;
    uint32_t step;
} Data;




uint32_t key;

//print to console
void render_to_console(Data data){
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("address:0x%08x\n",data.addr);
    printf("          %032b\n",data.addr);
    printf("value:  0x%08x\n",data.value);
    printf("          %032b\n",data.value);
    printf("step:   0x%08x\n",data.step<<2);
    printf("          %032b\n",data.step<<2);
    printf("read:   %d",data.read);
}



int main(){

    stdio_init_all();
    Data data;
    //set the address and get the value
    data.addr = (uint32_t *) 0x00000000;
    data.step = (uint32_t) 0x00000001;
    while (true) {
        key = getchar_timeout_us(0);
        switch(key){
            case 'r': // change r/w mode
                data.read = !data.read;
                break;
            case '=': // add step to address
                data.addr += data.step;
                break;
            case '-': // minus step to address
                data.addr -= data.step;
                break;
            // when shifting step, notice the maximum value and minimum value
            case 'a': // large scale left shift in step 
                data.step <<= 4u;
                if(!data.step)
                    data.step = (uint32_t) 0xf0000000;
                break;
            case 'd': // large scale right shift in step
                data.step >>= 4u;
                if(!data.step)
                    data.step = (uint32_t) 0x00000001;
                break;
            case 'w': // small scale left shift in step 
                data.step <<= 1u;
                if(!data.step)
                    data.step = (uint32_t) 0xf0000000;
                break;
            case 's': // small scale right shift in step 
                data.step >>= 1u;
                if(!data.step)
                    data.step = (uint32_t) 0x00000001;
                break;
        }
        if (key != PICO_ERROR_TIMEOUT){
            // print to console when any key is pressed
            if (data.read){
                data.value = register_read(data.addr);
            }
            render_to_console(data);
        }
        else {
            // print to console when no key pressed, with time delay prevent from keeping pringting
            render_to_console(data);
            sleep_ms(10);
        }
        





    }

}