#ifndef I2C_CFG_H_
#define I2C_CFG_H_

#define PCF8574_ADDR 0x4E >> 1
#define LCD_RS      0x01
#define LCD_RW      0x02
#define LCD_EN      0x04
#define FONT_LIGTH  0x08
/*#define I2C_MASTER_SDA_IO 8 //? GPIOS for ESP32-S3 (8 & 9)
#define I2C_MASTER_SCL_IO 9 //? In the esp32 wroom 32 the I2C buses are the GPIO 21 & 22*/


void init_i2c(void);
void lcd_i2c_init(void);
void lcd_i2c_write_cmd(char cmd_reg);
void lcd_i2c_write_data(char dat);
void lcd_i2c_wr_string(char *string);
void lcd_i2c_clear(void);
void lcd_set_pos(uint8_t row, uint8_t col);


#endif/*I2C_CFG_H_*/
