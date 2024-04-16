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
}