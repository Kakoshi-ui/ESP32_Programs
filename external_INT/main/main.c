#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void IRAM_ATTR input_callback(void *args){

    gpio_set_level(GPIO_NUM_5, 1);

}

void app_main(){
    
    gpio_set_direction(GPIO_NUM_5, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(GPIO_NUM_4);
    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_INPUT);
    gpio_set_intr_type(GPIO_NUM_4, GPIO_INTR_POSEDGE);
    
    gpio_install_isr_service(0);
    gpio_isr_handler_add(GPIO_NUM_4, input_callback, NULL);
    gpio_set_level(GPIO_NUM_2, 1);

    while(1){
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_5, 0);
    }

}