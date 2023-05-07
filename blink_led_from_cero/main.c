#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void app_main(void){

    volatile uint8_t led_state = 1;

    gpio_reset_pin(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2,GPIO_MODE_OUTPUT);

    while(1){
        
        gpio_set_level(GPIO_NUM_2,led_state);
        if(led_state == 1){
            printf("Led State: ON\n");
        }

        else if(led_state == 0){
            printf("Led State: OFF\n");

        }
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        
        led_state = !led_state;
    }
}
