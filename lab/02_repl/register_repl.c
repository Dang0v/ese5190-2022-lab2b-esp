#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"
#include "stdbool.h"
#include "hardware/gpio.h"
#include "registers.h"

#define STOP_CODE 22
#define HEXINPUT 1
#define BININPUT 0

#define VALID_HEX (k >= '0' && k <= '9') || (k >= 'a' && k <= 'f')
#define VALID_BIN k == '0' || k == '1'

typedef struct {
    ADDRESS addr;
    VALUE value;
    bool read;
    uint32_t step;
    uint32_t write;
    uint32_t mask;
} Data;

uint8_t key_input(uint8_t valid_input) {
    uint8_t k;
    switch (valid_input) {
        case HEXINPUT:
            while(true) {
                k = getchar_timeout_us(0);
                if (VALID_HEX){
                    putchar(k);
                    return k;
                }
            }
        case BININPUT:
            while(true) {
                k = getchar_timeout_us(0);
                if (VALID_BIN){
                    putchar(k);
                    return k;
                }
            }
    }
}

void get_input_string(uint8_t *buf, uint8_t valid_input) {
    int index = 32;
    if (valid_input)
        index = 8;
    for (int i = 0; i < index; ++i)
        buf[i] = key_input(valid_input);
}

void print_input_string(const uint8_t *buf, uint8_t valid_input) {
    int index = 32;
    if (valid_input)
        index = 8;
    printf("\n");
    for (int i = 0; i < index; ++i)
        printf("%c",buf[i]);
    printf("\n");
}

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
    printf("read:   %d\n",data.read);
    printf("write:  0x%08x\n",data.write);
    printf("          %032b\n",data.write);
    printf("mask:     %032b\n",data.mask);
}



int main(){

    stdio_init_all();
    Data data;
    //set the address and get the value
    data.addr = (uint32_t *) 0x00000000;
    data.step = (uint32_t) 0x00000001;
    data.write = (uint32_t) 0x00000000;
    data.mask = (uint32_t) 0x00000001;
    //initialize keyboard writing buffer
    uint8_t * write_buf = malloc(8 * sizeof(uint8_t));
    

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
            case 'h':
                printf("entre hex input:\n");
                write_buf = malloc(8 * sizeof(uint8_t));
                get_input_string(write_buf, HEXINPUT);
                //print_input_string(write_buf, HEXINPUT);
                data.write = strtol(write_buf, NULL, 16);
                break;
            case 'b':
                printf("entre bin input:\n");
                write_buf = malloc(32 * sizeof(uint8_t));
                get_input_string(write_buf, BININPUT);
                //print_input_string(write_buf, BININPUT);
                data.write = strtol(write_buf, NULL, 2);
                break;
            case 'x':
                * data.addr = data.write;
                break;
            case 'k':
                data.mask <<= 1u;
                if(!data.mask)
                    data.mask = (uint32_t) 0x80000000;
                break;
            case 'l':
                data.mask >>= 1u;
                if(!data.mask)
                    data.mask = (uint32_t) 0x00000001;
                break;
            case 'm':
                * data.addr = data.write & data.mask;
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
            sleep_ms(100);
        }
        





    }

}