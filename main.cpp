#include <stdio.h>
#include "pico/stdlib.h"

#include "S11059.h"

int main() {
    stdio_init_all();
    printf("Hello, world!\n");
    sleep_ms(1000);

    s11059_init();
    
    uint16_t red,green,blue;

    while (1) {
        s11059_read_data(&red,&green,&blue);
        printf("%d,%d,%d\n",red,green,blue);
    }
}