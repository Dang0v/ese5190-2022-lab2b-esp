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
    data.addr = (uint32_t *) 0x00000000;
    data.step = (uint32_t) 0x00000001;
    while (true) {
        key = getchar_timeout_us(0);
        switch(key){
            case 'r':
                data.read = !data.read;
                break;
            case '=':
                data.addr += data.step;
                break;
            case '-':
                data.addr -= data.step;
                break;
            case 'a':
                data.step <<= 4u;
                if(!data.step)
                    data.step = (uint32_t) 0xf0000000;
                break;
            case 'd':
                data.step >>= 4u;
                if(!data.step)
                    data.step = (uint32_t) 0x00000001;
                break;
            case 'w':
                data.step <<= 1u;
                if(!data.step)
                    data.step = (uint32_t) 0xf0000000;
                break;
            case 's':
                data.step >>= 1u;
                if(!data.step)
                    data.step = (uint32_t) 0x00000001;
                break;
        }
        if (key != PICO_ERROR_TIMEOUT){
            //printf("key = %d\n",key);
            if (data.read){
                data.value = register_read(data.addr);
            }
            render_to_console(data);
        }
        else {
            render_to_console(data);
            sleep_ms(10);
        }
        


// 1 = 49
// 2 = 50
// r = 114


    }

}