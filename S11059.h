#include "pico/binary_info.h"
#include "hardware/i2c.h"

#define S11059_I2C0_SDA 4
#define S11059_I2C0_SCL 5

#define S11059_I2C1_SDA 6
#define S11059_I2C1_SCL 7

#define S11059_address 0x2A

typedef struct
{
    // 0: LOW gain, 1: HIGH gain
    uint8_t gain;

    // 0b00:87.5us, 0b01:1.4ms, 0b10:22.4ms, 0b11:179.2ms
    uint8_t integration_time;
} S11059_Settings;

void s11059_init(i2c_inst_t *bus, S11059_Settings *settings)
{
    i2c_init(bus, 200 * 1000);

    if (bus == i2c0) {
        gpio_set_function(S11059_I2C0_SDA, GPIO_FUNC_I2C);
        gpio_set_function(S11059_I2C0_SCL, GPIO_FUNC_I2C);
        gpio_pull_up(S11059_I2C0_SDA);
        gpio_pull_up(S11059_I2C0_SCL);
        bi_decl(bi_2pins_with_func(S11059_I2C0_SDA, S11059_I2C0_SCL, GPIO_FUNC_I2C));
    } else if (bus == i2c1) {
        gpio_set_function(S11059_I2C1_SDA, GPIO_FUNC_I2C);
        gpio_set_function(S11059_I2C1_SCL, GPIO_FUNC_I2C);
        gpio_pull_up(S11059_I2C1_SDA);
        gpio_pull_up(S11059_I2C1_SCL);
        bi_decl(bi_2pins_with_func(S11059_I2C1_SDA, S11059_I2C1_SCL, GPIO_FUNC_I2C));
    }
}

void s11059_write_settings(i2c_inst_t *bus, S11059_Settings *settings)
{
    uint8_t buf[2];
    buf[0] = 0x00;
    buf[1] = 0b10000000 | ((settings->gain << 3) & 0b1000) | (settings->integration_time & 0b11);
    i2c_write_blocking(bus, S11059_address, buf, 2, false);
    buf[1] = ((settings->gain << 3) & 0b1000) | (settings->integration_time & 0b11);
    i2c_write_blocking(bus, S11059_address, buf, 2, false);
}

void s11059_read_data(i2c_inst_t *bus, uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *ir)
{
    uint8_t reg = 0x03;
    uint8_t buf[8];
    
    i2c_write_blocking(bus, S11059_address, &reg, 1, true);
    i2c_read_blocking(bus, S11059_address, buf, 8, false);
    *red   = buf[0] << 8 | buf[1];
    *green = buf[2] << 8 | buf[3];
    *blue  = buf[4] << 8 | buf[5];
    *ir    = buf[6] << 8 | buf[7];
}