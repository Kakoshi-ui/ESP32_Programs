#include <stdio.h>
#include "esp_system.h"
#include "esp_log.h"
#include "driver/adc.h"
#include "driver/gpio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TICKS_TO_WAIT       300
#define MAX_VOLT_VALUE      3100
#define MAX_DIGITAL_VALUE   4095
#define NUM_SAMPLES         32
static const char *TAG = "ADC";

void app_main(void){
    uint32_t adc_read = 0;
    uint32_t smooth_read = 0;

    adc1_config_channel_atten(ADC1_CHANNEL_1,ADC_ATTEN_DB_11);
    adc1_config_width(ADC_WIDTH_BIT_12);

    while(1){
        for(int i=0;i<NUM_SAMPLES;i++){
            adc_read = adc1_get_raw(ADC1_CHANNEL_1);
            smooth_read += adc_read;
        }
        smooth_read = smooth_read/NUM_SAMPLES;
        if (smooth_read > 4095)
        smooth_read = 4095;

        ESP_LOGI(TAG,"El valor crudo es:      %d",adc_read);
        ESP_LOGI(TAG,"El valor convertido es: %d",smooth_read);
        vTaskDelay(TICKS_TO_WAIT/portTICK_PERIOD_MS);
    }
}
