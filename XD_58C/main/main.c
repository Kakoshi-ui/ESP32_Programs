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
    ESP_LOGI(TAG, "Beginning");

    gpio_reset_pin(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    gpio_set_level(GPIO_NUM_2, 1);

    adc1_ch4_setup();
    init_nvs_flash();
    
    wifi_init_sta();
    ESP_LOGI(TAG, "..........wifi intialized succesfully");
    vTaskDelay(5000/portTICK_PERIOD_MS);

    volatile float xdc_read = 0.0;
    while (1){
        xdc_read = adc1_ch4_read();
        thingSpeak_post_data(xdc_read);
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
    
    ESP_LOGI(TAG, "Process terminated");
    for (int i = 0; i < 5; i++){
        ESP_LOGI(TAG, ".");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
