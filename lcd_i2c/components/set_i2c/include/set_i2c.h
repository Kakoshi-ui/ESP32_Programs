#ifndef SET_I2C_H_
#define SET_I2C_H_

void init_i2c(void);
void lcd_i2c_write_cmd(char cmd_reg);
void lcd_i2c_write_data(char dat);
void lcd_i2c_wr_string(char* string);
void lcd_i2c_init(void);

#endif /*SET_I2C_H_*/
