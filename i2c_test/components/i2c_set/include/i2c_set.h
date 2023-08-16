#ifndef I2C_SET_H_
#define I2C_SET_H_

#define I2C_SDA_PIN 19 //? GPIOS for ESP32-S3 (8 & 9)
#define I2C_SCL_PIN 18 //? In the esp32 wroom 32 the I2C buses are the GPIO 21 & 22


void init_i2c(void);
void lcd_i2c_init(void);
void lcd_i2c_write_cmd(char cmd_reg);
void lcd_i2c_write_data(char dat);
void lcd_i2c_wr_string(char *string);
void lcd_i2c_clear(void);
void lcd_set_pos(uint8_t row, uint8_t col);


#endif/*I2C_SET_H_*/
