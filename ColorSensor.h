#include "S11059.h"

/*
dat:0 none
:1 red
:2 blue
:3 yellow
*/

uint8_t color_read_data(i2c_inst_t *bus){
    uint8_t dat;

    uint16_t red,green,blue,ir;

    s11059_read_data(bus,&red,&green,&blue,&ir);
    printf("%d %d %d ",red,green,blue);

    if(red > 250 && green < 200 && blue < 200){
        dat = 1;
    }else if(red < 150 && green > 150 && blue > 230){
        dat = 2;
    }else if(red > 300 && green > 300 && blue < 200){
        dat = 3;
    }else{
        dat = 0;
    }
    return dat;
    /*Needs Adjustment*/
}