#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "com_set_HD44780U.h"
#include "freertos/task.h"
#include "esp_intr_alloc.h"
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "i2c_set.h"
#include "esp_log.h"

static const char* TAG = "i2c_test";

/**
 ** IMPORTANT UPGRADE TO 4.4.5 Version:
 ** Starting at this point the ESP-IDF version used is 4.4.5 review the changelog
 **/

void init_i2c(void){

    /*
     ** structure to init the i2c driver type i2c_config_t:
     ** Accepts the following params:
     ** mode: the mode of the MCU in the i2c bus: can be set in master or slave mode.
     ** sda_io_num: the gpio number for the sda bus
     ** scl_io_num: same as the last one but is for scl bus
     ** sda_pullup_en: enables the gpio pullup
     ** scl_pullup_en: same as before but for scl 
     *  master.clk_speed: parameter for master mode, the slave mode needs more parameters
     **/
    esp_err_t err,cfg_err;
    i2c_config_t i2c_setup = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = GPIO_NUM_21,      //! i2c_set_pin(882): scl and sda gpio numbers are the same
        .scl_io_num = GPIO_NUM_22,      //! for the esp32 wrooom 32
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000,
        .clk_flags = 0
    };
    cfg_err = i2c_param_config(I2C_MODE_MASTER,&i2c_setup);
    err = i2c_driver_install(I2C_NUM_0,I2C_MODE_MASTER,0,0,ESP_INTR_FLAG_LEVEL1);
    if(cfg_err != 0){
        ESP_LOGE(TAG,"I2C FAILED TO CONFIGURE DRIVER");
    } else if(err != 0){
        ESP_LOGE(TAG,"I2C FAILED TO INSTALL DRIVER");
    }
    else{
        ESP_LOGI(TAG,"I2C DRIVER INSTALLED SUCCESFULLY");
    }

}

void lcd_i2c_write_cmd(char cmd_reg){

    /*
     * At this point is important know, how to write to the LCD HD44780U with the i2c module PCF8574?:
     * The LCD works in two modes: 4-bit or 8-bit mode. The most of the LCD modules come with the i2c module
     * solder in but isn´t joint in the best way.
     * 
     * Apart of the data/command bit´s the LCD module needs almost 3 bits more of comands to acknowledge wath to do
     * with the data/command bit´s wich are EN, RS & RW.
     * The i2c module only convert the serial data to parallel, the way in wich the pins are disposed is the next:
     * i2c_module | LCD_module
     * -----------|------------
     *    B0      |     RS
     *    B1      |     RW
     *    B2      |     EN
     *    B3      | Not Conected
     *    B4      |     B4
     *    B5      |     B5
     *    B6      |     B6
     *    B7      |     B8
     *  
     *  For this case is imposible use the 8-bit mode so, is important to set the LCD module in 4-bit mode and use
     *  the restant bits to send commands, this method was maded for that case.
     *  To send commands the method saves the first upper data bits and send the commands with the 4 lower bits
     *  
     *  For more specific info abaut the LCD function please review the HD44780U datasheet in it are described all the
     *  function modes and the way in wich operates the module
     */
    esp_err_t err;

    uint8_t cmd_buff[4];//Data buffer sent to the LCD module
    // First, save the upper 4 bits and send the data commands
    cmd_buff[0] = (cmd_reg & 0xF0)|LCD_EN|FONT_LIGTH;            //EN = 1|RW = 0
    // Then needs to send again the last bits but clear in EN bit
    cmd_buff[1] = (cmd_reg & 0xF0)|FONT_LIGTH;                   //EN = 0|RW = 0
    // Send the lower lower 4 bits with the respective commands
    cmd_buff[2] = ((cmd_reg << 4) & 0xF0)|LCD_EN|FONT_LIGTH;     //EN = 1|RW = 0
    // Send again the last instruction but with EN bit clear
    cmd_buff[3] = ((cmd_reg << 4) & 0xF0)|FONT_LIGTH;            //EN = 0|RW = 0

    err = i2c_master_write_to_device(I2C_NUM_0,PCF8574_ADDR,
                                    cmd_buff,4,100);  //! ERROR sending commands, check out the method
    if (err != 0) {
        ESP_LOGE(TAG,"I2C: ERROR(%d) WHEN TRYNG TO SEND COMMAND",err);
    } else{
        ESP_LOGI(TAG,"I2C: SUCCESFULLY SENDED COMAND: %d",cmd_reg);
    }
}

void lcd_i2c_write_data(char dat){
    //* For data mode transfer the way is the same as the command mode, only changes that needs the RS bit set for data transfer
    esp_err_t err;
    uint8_t dat_buff[4];
    dat_buff[0] = (dat & 0xF0)|LCD_RS|LCD_EN|FONT_LIGTH;
    dat_buff[1] = (dat & 0xF0)|FONT_LIGTH;
    dat_buff[2] = ((dat << 4) & 0xF0)|LCD_RS|LCD_EN|FONT_LIGTH;
    dat_buff[3] = ((dat << 4) & 0xF0)|FONT_LIGTH;
    err = i2c_master_write_to_device(I2C_NUM_0,PCF8574_ADDR<<1,
                                    dat_buff,4,100);     //! ERROR sending data, check out the method
    if (err != 0) ESP_LOGE(TAG,"I2C ERROR: FAILED TO SEND DATA");
}

void lcd_i2c_wr_string(char *string){

    //* Chek out this method it really works!!!
    while(*string) lcd_i2c_write_data(*string++);

}

void lcd_i2c_init(void){

    /* 
     * LCD initialization: the manufacturer provides a way to initalize the module
     * please see the HD44780U datasheet page 46.
     */
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

    //display initialization
    lcd_i2c_write_cmd(0x28);
    vTaskDelay(pdMS_TO_TICKS(1));

    lcd_i2c_write_cmd(0x30);

    lcd_i2c_write_cmd(0x08);
    vTaskDelay(pdMS_TO_TICKS(1));

    lcd_i2c_write_cmd(0x01);
    vTaskDelay(pdMS_TO_TICKS(1));

    lcd_i2c_write_cmd(0x06);
    ESP_LOGI(TAG,"I2C SUCCESFULLY INITIALIZED");
}

void lcd_i2c_clear(void){

    lcd_i2c_write_cmd(0x01);
    vTaskDelay(pdMS_TO_TICKS(5));
    ESP_LOGI(TAG,"I2C DISPLAY CLEARED");

}

void lcd_set_pos(uint8_t row, uint8_t col){

    switch (row){
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }
    lcd_i2c_write_cmd(col);
    ESP_LOGI(TAG,"I2C POSITION: ROW %d",row);
}