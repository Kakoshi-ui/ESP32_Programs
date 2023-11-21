#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "oled_i2c_stp.h"

void app_main(void){

    i2c_setup();

    oled_init_secuence();

    oled_black_white();
    i2c_oled_cmd(SET_DISPLAY_OFF);
    vTaskDelay(5000/portTICK_PERIOD_MS);

    display_img(gengar0_bmp_img);
    i2c_oled_cmd(SET_DISPLAY_OFF);
    vTaskDelay(5000/portTICK_PERIOD_MS);

    display_img(display_buffer);
    i2c_oled_cmd(SET_DISPLAY_OFF);
    vTaskDelay(1/portTICK_PERIOD_MS);

    display_img(gengar1_bmp_img);
    i2c_oled_cmd(SET_DISPLAY_OFF);
    vTaskDelay(5000/portTICK_PERIOD_MS);

    display_img(display_buffer);
    i2c_oled_cmd(SET_DISPLAY_OFF);
    vTaskDelay(1/portTICK_PERIOD_MS);

    display_img(gengar0_bmp_img);
    i2c_oled_cmd(SET_DISPLAY_OFF);
    vTaskDelay(5000/portTICK_PERIOD_MS);

    display_img(display_buffer);

    while(1){
        drawPixel(64,16,WHITE);
        display_img(display_buffer);
        i2c_oled_cmd(SET_DISPLAY_OFF);
        vTaskDelay(1000/portTICK_PERIOD_MS);

        drawPixel(64,16,BLACK);
        display_img(display_buffer);
        i2c_oled_cmd(SET_DISPLAY_OFF);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    /*drawPixel(0,0,WHITE);
    drawPixel(64,16,WHITE);
    display_img(display_buffer);*/
    
}
