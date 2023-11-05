#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <esp_log.h>
#include "adc_set.h"
#include "thingspeak.h"
#include "wifi_sta.h"

static const char *TAG = "MAIN";

void app_main(void){
    gpio_reset_pin(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    gpio_set_level(GPIO_NUM_2, 1);

    init_nvs_flash();
    
    wifi_init_sta();
    ESP_LOGI(TAG, "..........wifi intialized succesfully");
    vTaskDelay(1000/portTICK_PERIOD_MS);

    float test0 = 5.25, test1 = 7.02;
    thingSpeak_post_data(test0);
    vTaskDelay(2000/portTICK_PERIOD_MS);
    thingSpeak_post_data(test1);
    ESP_LOGI(TAG, "Process terminated");
    for (int i = 0; i < 5; i++){
        ESP_LOGI(TAG, ".");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
