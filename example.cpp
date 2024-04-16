#include <stdio.h>
#include "pico/stdlib.h"

#include "S11059.h"

#define S11059_I2C_BUS i2c0

int main()
{
    stdio_init_all();
    printf("Hello, world!\n");
    sleep_ms(1000);

    S11059_Settings settings;
    settings.gain = 1;
    settings.integration_time = 0b01;

    s11059_init(S11059_I2C_BUS);
    s11059_write_settings(S11059_I2C_BUS, &settings);

    while (true)
    {
        uint16_t red, green, blue, ir;
        s11059_read_data(S11059_I2C_BUS, &red, &green, &blue, &ir);
        printf("Red: %d, Green: %d, Blue: %d, IR: %d\n", red, green, blue, ir);
        sleep_ms(1000);
    }
}
