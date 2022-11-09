#include "pico/stdlib.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "hardware/gpio.h"
#include "neopixel.h"


#define STOP_CODE 22

const uint CAPTURE_PIN_BASE = 21;
const uint CAPTURE_N_SAMPLES = 512;

const uint NUMBER_BUF_SIZE = 7;

bool judge_value(const uint8_t *capture_buf, int index) {
    if (capture_buf[index] == 1)
        return 1;
    else 
        return 0;
}

void record_pin(uint8_t *capture_buf, uint pin_base, uint n_sample) {
    for (int index = 0; index < n_sample; ++index){
        capture_buf[index] = !(gpio_get(pin_base));
        sleep_ms(10);
    }
}

uint8_t key_number() {
    uint8_t k;
    while(true) {
        k = getchar_timeout_us(0);
        if (k >= '0' && k <= '9' ){
            putchar(k);
            return k;
        }
        else if (k == '=')
            return STOP_CODE;
    }
}

uint8_t get_number_string(uint8_t *buf, uint8_t start_index) {
    int index = 3;
    uint8_t number[3];
    for (int i = 0; i < 3; ++i){
        if ((number[i] = key_number()) == STOP_CODE){
            index = i;
            break;
        }
    }
    //copy the valid part into a new array
    for (int i = start_index; i < index + start_index; ++i){
        buf[i] = number[i-start_index];
    }
    return index;
}

// input is only valid for 0 and 1, = for stop
int key_input(bool keep) {
    char k;
    while(keep) {
        k = getchar_timeout_us(0);
        if (k == '1'){
            putchar(k);
            return 1;
        }  
        else if (k == '0'){
            putchar(k);
            return 0;
        }
        else if (k == '=')
            return STOP_CODE;
    }
}

void record_keyboard(uint8_t *capture_buf, uint n_sample) {
    int k;
    bool keep = 1;
    for (int index = 0; index < n_sample; ++index){
        if ((capture_buf[index] = key_input(keep)) == STOP_CODE)
            keep = 0;
    }
}

void print_capture_buf(const uint8_t *buf, uint pin_base, uint n_sample) {
    printf("Capture:\n");
    for (int index = 0; index < n_sample; ++index){
        //printf(buf[index] ? "-" : "_");
        printf("%d",buf[index]);
    }
    printf("\n");
}

void play_record(const uint8_t *buf, uint n_sample, double velocity, uint times) {
    printf("Start playing record...\n");
    uint32_t t = (uint32_t)(10000 / velocity);
    for (int i = 0; i < times; ++i) {
        for (int index = 0; index < n_sample; ++index) {
            if (judge_value(buf, index)){
                neopixel_set_rgb(0x00ff0000);
            }
            else
                neopixel_set_rgb(0x00000000);
            sleep_us(t);
        }
        neopixel_set_rgb(0x00ffffff);
        sleep_ms(500);
        neopixel_set_rgb(0x00000000);
    }
    
}

void clear_buf (uint8_t *buf, uint length) {
    for (int index = 0; index < length; ++index)
        buf[index] = 0;
}

char key = 0;
double velocity = 1;
uint times = 1;

uint8_t integer_length = 0;
uint8_t total_length = 0;

int main() {
    stdio_init_all();
    sleep_ms(5000);


    uint8_t * capture_buf = malloc(CAPTURE_N_SAMPLES * sizeof(uint8_t));
    uint8_t * number_buf = malloc(NUMBER_BUF_SIZE * sizeof(char));

    neopixel_init();
    neopixel_set_rgb(0x00000000);

    gpio_init(CAPTURE_PIN_BASE);
    gpio_set_dir(CAPTURE_PIN_BASE, GPIO_IN);

    printf("Sequencer started.\n");
    printf("press h for help:\n");
    while(true) {
        key = getchar_timeout_us(0);
        switch(key){
            case 'h': 
                printf("    b           record from boot pin\n");
                printf("    p           play most recent record\n");
                printf("    k           record from key board\n");
                printf("    c           clear stored signal\n");
                printf("\n");
                break;
            case 'b':
                printf("Recording from boot pin\n");
                record_pin(capture_buf, CAPTURE_PIN_BASE, CAPTURE_N_SAMPLES);
                printf("Recording done!\n");
                print_capture_buf(capture_buf, CAPTURE_PIN_BASE, CAPTURE_N_SAMPLES);
                break;
            case 'p':
                //set the play speed
                clear_buf(number_buf, NUMBER_BUF_SIZE);
                printf("please enter the speed multiplier:\n");

                printf("Integer part:\n");
                integer_length = get_number_string(number_buf, 0);
                number_buf[integer_length] = 46u; // 46u represent fo "."
                printf("\nfractional part:\n");
                //combine to a string
                total_length = get_number_string(number_buf, integer_length + 1) + integer_length + 1;
                //transfer to float
                
                velocity = atof(number_buf);
                printf("%3.3f",velocity);
                if (velocity == 0)
                    velocity = 1;
                
                //set the loop times
                clear_buf(number_buf, NUMBER_BUF_SIZE);
                printf("\nplease enter loop times:\n");
                get_number_string(number_buf, 0);
                times = atoi(number_buf);

                printf("\nThe record will be play at %f of default speed and %d times\n", velocity, times);
                play_record(capture_buf, CAPTURE_N_SAMPLES, velocity, times);
                print_capture_buf(capture_buf, CAPTURE_PIN_BASE, CAPTURE_N_SAMPLES);
                printf("Done!\n");
                break;
            case 'k':
                printf("Recording from keyboard\n");
                printf("Print = to finish\n");
                record_keyboard(capture_buf, CAPTURE_N_SAMPLES);
                printf("Done!\n");
                break;
            case 'c':
                clear_buf(capture_buf, CAPTURE_N_SAMPLES);
                printf("Clear!\n");
                break;
            
        }
    }
}


