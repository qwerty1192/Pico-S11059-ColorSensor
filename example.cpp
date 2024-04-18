#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "ColorSensor.h"

#define S11059_I2C_BUS i2c0
#define S11059_I2C_BUS2 i2c1

int main() {
    //To use USB
    stdio_init_all();
    printf("Hello, world!\n");
    sleep_ms(1000);

    S11059_Settings settings;
    settings.gain = 1;
    settings.integration_time = 0b01;

    s11059_init(S11059_I2C_BUS, &settings);
    s11059_init(S11059_I2C_BUS2, &settings);

    uint8_t dat,dat2;

    //Loop
    while (true)
    {
        dat = color_read_data(S11059_I2C_BUS);
        if(dat == 0){
            printf("None ");
        }else if(dat == 1){
            printf("Red ");
        }else if(dat == 2){
            printf("Blue ");
        }else{
            printf("Yellow ");
        }
        dat2 = color_read_data(S11059_I2C_BUS2);
        if(dat2 == 0){
            printf("None\n");
        }else if(dat2 == 1){
            printf("Red\n");
        }else if(dat2 == 2){
            printf("Blue\n");
        }else{
            printf("Yellow\n");
        }
        sleep_ms(10);
    }
}
