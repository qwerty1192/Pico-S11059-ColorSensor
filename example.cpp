#include <stdio.h>
#include "pico/stdlib.h"

#include "S11059.h"

int main() {
    stdio_init_all();
    printf("Hello, world!\n");
    sleep_ms(1000);

    S11059_Settings settings {
        .gain = 1,
        .integration_time = 0b10
    };

    s11059_init(&settings);
    
    uint16_t red,green,blue,ir;

    while (1) {
        settings.gain = 1;
        s11059_write_settings(&settings);
        sleep_ms(1000);
        s11059_read_data(&red,&green,&blue,&ir);
        printf("HIGH GAIN:\n");
        printf(" RED:%d GREEN:%d BLUE:%d IR:%d\n",red,green,blue,ir);
        printf(" RED:   %d\n", s11059_read_data_red());
        printf(" GREEN: %d\n", s11059_read_data_green());
        printf(" BLUE:  %d\n", s11059_read_data_blue());
        printf(" IR:    %d\n", s11059_read_data_ir());

        settings.gain = 0;
        s11059_write_settings(&settings);
        sleep_ms(1000);
        s11059_read_data(&red,&green,&blue,&ir);
        printf("LOW GAIN:\n");
        printf(" RED:%d GREEN:%d BLUE:%d IR:%d\n",red,green,blue,ir);
        printf(" RED:   %d\n", s11059_read_data_red());
        printf(" GREEN: %d\n", s11059_read_data_green());
        printf(" BLUE:  %d\n", s11059_read_data_blue());
        printf(" IR:    %d\n", s11059_read_data_ir());

        sleep_ms(1000);
    }
}