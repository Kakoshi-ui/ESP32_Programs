#include <stdio.h>
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_intr_alloc.h"
#include "com_set_HD44780U.h"
#include "set_i2c.h"

char row_1 [2]={0,64};

void init_i2c(void){

    //Configuration of the i2c protocol, set in master mode
    //In this case the structure to configure the i2c peripheral is quite specific
    //so it don´t need to explain much to understand it
    i2c_config_t i2c_setup = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = GPIO_NUM_21,
        .scl_io_num = GPIO_NUM_22,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000,
        .clk_flags = 0
    };
    i2c_param_config(I2C_MODE_MASTER,&i2c_setup);
    i2c_driver_install(I2C_NUM_0,i2c_setup.mode,0,0,0);
}

void lcd_i2c_write_cmd (char cmd_reg){

    uint8_t data_buffer[4];
    data_buffer[0]=(cmd_reg & 0xF0)|LCD_EN|FONT_LIGTH;
    data_buffer[1]=(cmd_reg & 0xF0)|FONT_LIGTH;
    data_buffer[2]=((cmd_reg << 4) & 0xF0)|LCD_EN | FONT_LIGTH;
    data_buffer[3]=((cmd_reg << 4) & 0xF0)|FONT_LIGTH;  

    i2c_master_write_to_device(I2C_NUM_0,PCF8574_SLV_ADDR_W,
                                data_buffer,4,10);
}

void lcd_i2c_write_data(char dat){

    uint8_t data_buffer[4];
    data_buffer[0]=(dat & 0xF0)|LCD_RS|LCD_EN|FONT_LIGTH;
    data_buffer[1]=(dat & 0xF0)|LCD_RS|FONT_LIGTH;
    data_buffer[2]=((dat << 4) & 0xF0)|LCD_RS|LCD_EN|FONT_LIGTH;
    data_buffer[3]=((dat << 4) & 0xF0)|LCD_RS|FONT_LIGTH;

    i2c_master_write_to_device(I2C_NUM_0,PCF8574_SLV_ADDR_W,
                                data_buffer,4,10);
}

void lcd_i2c_wr_string(char *string){

    while(*string) lcd_i2c_write_data(*string++);

}

void lcd_i2c_init(void){

    //set to 4-bit mode
    vTaskDelay(pdMS_TO_TICKS(60));

    lcd_i2c_write_cmd(0x30);
    vTaskDelay(pdMS_TO_TICKS(10));
    
    lcd_i2c_write_cmd(0x30);
    vTaskDelay(pdMS_TO_TICKS(1));

    lcd_i2c_write_cmd(0x30);
    vTaskDelay(pdMS_TO_TICKS(1));

    lcd_i2c_write_cmd(0x20);
    vTaskDelay(pdMS_TO_TICKS(1));

    lcd_i2c_write_cmd(0x20);
    vTaskDelay(pdMS_TO_TICKS(1));

    //Display initialization
    lcd_i2c_write_cmd(0x28);
    vTaskDelay(pdMS_TO_TICKS(1));
    
    lcd_i2c_write_cmd(0x30);

    lcd_i2c_write_cmd(0x08);
    vTaskDelay(pdMS_TO_TICKS(1));

    lcd_i2c_write_cmd(0x01);
    vTaskDelay(pdMS_TO_TICKS(1));

    lcd_i2c_write_cmd(0x06);
}