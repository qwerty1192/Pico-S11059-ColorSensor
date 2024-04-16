<<<<<<< HEAD
#include "S11059.h"

/*
dat:0 none
:1 red
:2 blue
:3 yellow

Select_Sensor:0 i2c0
:1 i2c1
*/

uint8_t color_read_data(uint8_t Select_Sensor){
    uint8_t dat;

    uint16_t red,green,blue,ir;

    s11059_read_data(&red,&green,&blue,&ir,Select_Sensor);
    //printf("%d %d %d\n",red,green,blue);

    if(red > 250 && green < 250 && blue < 250){
        dat = 1;
    }else if(red < 150 && green > 150 && blue > 250){
        dat = 2;
    }else if(red > 300 && green > 300 && blue < 200){
        dat = 3;
    }else{
        dat = 0;
    }
    return dat;
    /*Needs Adjustment*/
=======
#include "S11059.h"

void color_read_data(uint16_t *Isred, uint16_t *Isblue, uint16_t *Isyellow){
    S11059_Settings settings;
    settings.gain = 1;
    settings.integration_time = 0b01;

    s11059_init(&settings);

    uint16_t red,green,blue,ir;

    s11059_write_settings(&settings);
    sleep_ms(15);
    s11059_read_data(&red,&green,&blue,&ir);
    *Isred = 0;
    *Isblue = 0;
    *Isyellow = 0;

    if(red > 250 && blue < 250 && green < 250){
        *Isred = 1;
    }else if(red < 250 && blue > 300 && green > 250){
        *Isblue = 1;
    }else if(red > 350 && blue < 250 && green > 350){
        *Isyellow = 1;
    }
    /*Needs Adjustment*/

    sleep_ms(10);
}

void color_read_data2(uint16_t *Isred, uint16_t *Isblue, uint16_t *Isyellow){
    S11059_Settings settings;
    settings.gain = 1;
    settings.integration_time = 0b01;

    s11059_init(&settings);

    uint16_t red,green,blue,ir;

    s11059_write_settings(&settings);
    sleep_ms(15);
    s11059_read_data_2(&red,&green,&blue,&ir);
    printf("%d %d %d\n",red,green,blue);
    *Isred = 0;
    *Isblue = 0;
    *Isyellow = 0;

    if(red > 250 && blue < 250 && green < 250){
        *Isred = 1;
    }else if(red < 250 && blue > 300 && green > 250){
        *Isblue = 1;
    }else if(red > 300 && blue < 200 && green > 300){
        *Isyellow = 1;
    }
    /*Needs Adjustment*/

    sleep_ms(10);
>>>>>>> origin/use-2-sensor-on-1-mcu
}