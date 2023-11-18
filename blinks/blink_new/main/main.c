#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

#define STACK_SIZE 1024

void blink_led(void* vParameters){
    gpio_reset_pin(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    volatile uint8_t gpio_lvl = 1;
    while (1){
        gpio_lvl ^= 1;
        gpio_set_level(GPIO_NUM_2, gpio_lvl);
    }
}

void app_main(void){
    static uint8_t ucParametersToPass;
    TaskHandle_t task_handler;
    xTaskCreate(    blink_led, 
                    "blink_led",
                    STACK_SIZE,
                    &ucParametersToPass,
                    1,
                    &task_handler);
    
}
