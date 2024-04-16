#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#include "ColorSensor.h"

void main(void) {
    //To use USB
    stdio_init_all();
    printf("Hello, world!\n");
    sleep_ms(1000);

    S11059_Settings settings;
    settings.gain = 1;
    settings.integration_time = 0b01;

    s11059_init(&settings);

    uint8_t dat;

    gpio_init(10);
    gpio_init(11);
    gpio_init(12);
    gpio_init(13);
    gpio_set_dir(10, GPIO_OUT);
    gpio_set_dir(11, GPIO_OUT);
    gpio_set_dir(12, GPIO_OUT);
    gpio_set_dir(13, GPIO_OUT);

    adc_init();
    adc_gpio_init(31);
    adc_select_input(0);
    //Loop
    while (true)
    {
        dat = color_read_data(1);
        if(dat == 1){
            gpio_put(10, 1);
            gpio_put(11, 0);
            gpio_put(12, 0);
            gpio_put(13, 0);
        }else if(dat == 2){
            gpio_put(10, 0);
            gpio_put(11, 1);
            gpio_put(12, 0);
            gpio_put(13, 0);
        }else if(dat == 3){
            gpio_put(10, 0);
            gpio_put(11, 0);
            gpio_put(12, 1);
            gpio_put(13, 0);
        }else{
            gpio_put(10, 0);
            gpio_put(11, 0);
            gpio_put(12, 0);
            gpio_put(13, 0);
        }
    }
}
