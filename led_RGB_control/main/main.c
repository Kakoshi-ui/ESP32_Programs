#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define led_R 0x01
#define led_int 0x02
#define led_B 0x03
#define led_G 0x04

void app_main(void){

    gpio_reset_pin(led_R);
    gpio_reset_pin(led_int);
    gpio_reset_pin(led_B);
    gpio_reset_pin(led_G);

    gpio_set_direction(led_R,GPIO_MODE_OUTPUT);
    gpio_set_direction(led_int,GPIO_MODE_OUTPUT);
    gpio_set_direction(led_B,GPIO_MODE_OUTPUT);
    gpio_set_direction(led_G,GPIO_MODE_OUTPUT);

    gpio_set_level(led_int,1);
    printf("Start Cycle");

    while (1){
        gpio_set_level(led_R,1);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        gpio_set_level(led_R,0);
        gpio_set_level(led_G,1);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        gpio_set_level(led_G,0);
        gpio_set_level(led_B,1);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        gpio_set_level(led_B,0);
        
    }

}
