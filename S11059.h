#include "pico/binary_info.h"
#include "hardware/i2c.h"

#define S11059_i2c i2c0
#define S11059_SDA_PIN 4
#define S11059_SCL_PIN 5

#define S11059_address 0x2A

struct S11059_Settings {
    // 0: LOW gain, 1: HIGH gain
    uint8_t gain;

    // 0: fixed_time, 1: manual_setting
    uint8_t integration_mode;

    // fixed_time_mode:
    //   00:87.5us, 01:1.4ms, 10:22.4ms, 11:179.2ms
    // manual_setting_mode:
    //   00:175*Nus, 01:2.8*Nms, 10:44.8*Nms, 11:358.4*Nms
    uint8_t integration_time_mode;

    // N: 0x0000-0xFFFF
    // use only integration_mode=1
    uint16_t manual_setting_time;
};

void s11059_init() {
    i2c_init(S11059_i2c, 100 * 1000);
    gpio_set_function(S11059_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(S11059_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(S11059_SDA_PIN);
    gpio_pull_up(S11059_SCL_PIN);

    bi_decl(bi_2pins_with_func(S11059_SDA_PIN, S11059_SCL_PIN, GPIO_FUNC_I2C));

    uint8_t buf[2];
    buf[0] = 0x00;
    buf[1] = 0b10001011;
    i2c_write_blocking(S11059_i2c,S11059_address,buf,2,false);
    buf[1] = 0b00001011;
    i2c_write_blocking(S11059_i2c,S11059_address,buf,2,false);
}

void s11059_read_data(uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *ir) {
    uint8_t reg = 0x03;
    uint8_t buf[8];
    i2c_write_blocking(S11059_i2c,S11059_address,&reg,1,true);
    i2c_read_blocking(S11059_i2c,S11059_address,buf,8,false);
    *red   = buf[0]<<8 | buf[1];
    *green = buf[2]<<8 | buf[3];
    *blue  = buf[4]<<8 | buf[5];
    *ir    = buf[6]<<8 | buf[7];
}