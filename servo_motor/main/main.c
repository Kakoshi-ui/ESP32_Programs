#include <stdio.h>
#include <esp_system.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <driver/adc.h>
#include <driver/ledc.h>
#include <esp_log.h>
#include "pwm_setup.h"

static const char* TAG = "MAIN";

void adc1_ch4_setup(void){
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);
    adc1_config_width(ADC_WIDTH_BIT_12);
}

uint16_t adc1_ch4_read(void){
    uint16_t adc_raw_read = 0;
    adc_raw_read = adc1_get_raw(ADC_CHANNEL_4);
    return adc_raw_read;
}

void app_main(void){
    gpio_reset_pin(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_2, 1);
    
    volatile uint16_t read;
    init_pwm();

    while (1){
        read = adc1_ch4_read();
        ESP_LOGI(TAG, "adc read: %i", read);
        set_pwm_pos(read);
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}
