#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


static uint8_t led=2;
uint8_t led_state = 0;

esp_err_t init_led(void){

    gpio_reset_pin(led);
    gpio_set_direction(led,GPIO_MODE_OUTPUT);
    return ESP_OK;

}

esp_err_t blink(void){

    led_state = !led_state;
    gpio_set_level(led,led_state);
    return ESP_OK;

}

void app_main(void){

    init_led();
    while(1){

        vTaskDelay(200 / portTICK_PERIOD_MS);
        blink();
        printf("%u\n",led_state);

    }

}
