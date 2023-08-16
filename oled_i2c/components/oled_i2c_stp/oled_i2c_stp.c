#include <stdio.h>
#include <string.h>
#include <stdint-gcc.h>
#include "esp_intr_alloc.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "oled_i2c_stp.h"

static const char* TAG = "I2C-OLED: ";

void i2c_setup(void){

    esp_err_t param_err,instDrv_err;

    //Initializing the i2c driver:
    i2c_config_t i2c_cfg_str = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = GPIO_NUM_8,
        .scl_io_num = GPIO_NUM_9,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000,
        .clk_flags = 0
    };
    param_err = i2c_param_config(I2C_NUM_0,&i2c_cfg_str);
    instDrv_err = i2c_driver_install(I2C_NUM_0,I2C_MODE_MASTER,0,0,ESP_INTR_FLAG_LEVEL1);

    if(param_err != 0){
        ESP_LOGE(TAG,"FAILED TO CONFIG PARAMS");
    } else if (instDrv_err != 0){
        ESP_LOGE(TAG,"FAILED INSTALLING DRIVER");
    }
    else{
        ESP_LOGI(TAG,"PARAMS INSTALLED CORRECTLY");
    }
}

void i2c_oled_cmd(uint8_t cmd_reg){

    //* In this example we are using the large method described in the ESP-Programming Guide

    esp_err_t cmd_begin_err,write_err;
    uint8_t cmd_buff[2];

    cmd_buff[0] = WR_COMMAND;
    cmd_buff[1] = cmd_reg;

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);

    i2c_master_write_byte(cmd,(SSD1306_SLV_ADDR<<1)|I2C_MASTER_WRITE,true);
    write_err = i2c_master_write(cmd,cmd_buff,2,true);

    i2c_master_stop(cmd);
    cmd_begin_err = i2c_master_cmd_begin(I2C_NUM_0,cmd,1);

    i2c_cmd_link_delete(cmd);

    if (write_err != 0){
        ESP_LOGE(TAG,"ERROR N.%d WHILE WRITING COMMAND",write_err);
    } else if (cmd_begin_err != 0){
        ESP_LOGE(TAG,"ERROR N.%d WHILE SENDING COMMAND",cmd_begin_err);
    }
    else{
        ESP_LOGI(TAG,"COMMAND SEND SUCCESFULLY");
    } 
}

void i2c_oled_data(uint8_t data_recived){

    uint8_t data_buffer[2];
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    
    data_buffer[0]= WR_DATA;
    data_buffer[1]= data_recived;

    i2c_master_start(cmd);

    i2c_master_write_byte(cmd,(SSD1306_SLV_ADDR<<1)|I2C_MASTER_WRITE,true);
    i2c_master_write(cmd,data_buffer,2,true);

    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_0,cmd,10);
    i2c_cmd_link_delete(cmd);

}

void oled_black_white(void){

    for (int j = 0; j < 32; j++){
        for(int i=0; i<16; i++){
            i2c_oled_data(0);
        }
        for (int i=0; i<16; i++){
            i2c_oled_data(1);
        }
    }
    
}

void drawPixel(int16_t x, int16_t y, uint16_t color){
    if (x >= 0 && x < DISPLAY_WIDTH && y >= 0 && y < DISPLAY_HEIGHT){
        switch(color){
            case WHITE:     display_buffer[x + (y/8) * DISPLAY_WIDTH] |=  (1 << (y & 7)); break;
            case BLACK:     display_buffer[x + (y/8) * DISPLAY_WIDTH] &= ~(1 << (y & 7)); break;
            case INVERSE:   display_buffer[x + (y/8) * DISPLAY_WIDTH] ^=  (1 << (y & 7)); break;
        }
    }
    
}

void display_img(const unsigned char* image){

    for (int i = 0; i < ((DISPLAY_WIDTH*DISPLAY_HEIGHT)/8); i++){
        i2c_oled_data(image[i]);
    }
    
    //! Hay que cambiar el método
    /*esp_err_t wr_img_err,img_bgn_err;

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    
    i2c_master_write_byte(cmd,(SSD1306_SLV_ADDR << 1)|I2C_MASTER_WRITE,true);
    wr_img_err = i2c_master_write(cmd,image,(DISPLAY_WIDTH*DISPLAY_HEIGHT)/8,true);

    i2c_master_stop(cmd);
    img_bgn_err = i2c_master_cmd_begin(I2C_NUM_0,cmd,10);
    i2c_cmd_*/

}

void i2c_oled_clear_scrn(void){

    memset(display_buffer,0x00,512);
    display_img(display_buffer);

}

void oled_init_secuence(void){

    //* The init Secuence is described in the SSD1306 DataSheet:

    // Set Display off
    i2c_oled_cmd(SET_DISPLAY_OFF);
    
    i2c_oled_cmd(SET_DISPLAY_CLOCK);
    i2c_oled_cmd(0x80);

    i2c_oled_cmd(SET_MULTIPLEX_RATIO);
    i2c_oled_cmd(64-1);

    i2c_oled_cmd(SET_DISPLAY_OFFSET);
    i2c_oled_cmd(0x00);

    i2c_oled_cmd(SET_DISPlAY_START_LINE);
    
    //Charge Pump
    i2c_oled_cmd(0x8D);
    i2c_oled_cmd(0x14);

    i2c_oled_cmd(SET_MEMORY_ADDRESS_MODE);
    i2c_oled_cmd(0x00);

    i2c_oled_cmd(SET_SEGMENT_RE_MAP | 0x01);

    i2c_oled_cmd(SET_COM_OUTPUT_SCAN_DIRECTION | 0x08);

    i2c_oled_cmd(SET_COM_PINS);
    i2c_oled_cmd(0xA4);

    i2c_oled_cmd(SET_CONTRAST_CONTROL);
    i2c_oled_cmd(0xCF);

    i2c_oled_cmd(SET_PRE_CHARGE_PERIOD);
    i2c_oled_cmd(0xF1);

    i2c_oled_cmd(SET_VCOMH_DESELECT_LEVEL);
    i2c_oled_cmd(0x40);

    i2c_oled_cmd(ENTIRE_DISPLAY_OFF);

    i2c_oled_cmd(SET_NORMAL_DISPLAY);

    i2c_oled_cmd(SET_DISPLAY_ON);

    i2c_oled_cmd(SET_COLUMN_ADDRESS);
    i2c_oled_cmd(0x00);
    i2c_oled_cmd(0x7F);

    i2c_oled_cmd(SET_PAGE_ADDRESS);
    i2c_oled_cmd(0x00);
    i2c_oled_cmd(0x07);
}