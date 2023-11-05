#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <driver/adc.h>

static const char *TAG = "ESP_ADC";

void adc1_ch4_setup(void){
    //Configuring adc attenuation in 11 decibels, max voltage 2450mV
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);
    //adc bits width: 12 bits
    adc1_config_width(ADC_WIDTH_BIT_12);
}

float adc1_ch4_read(void){
    uint32_t adc_raw_read = 0, adc_input = 0;
    float adc_sampled = 0.0, adc_conv_data = 0.0;
    //smoothing process, taking 32 samples:
    for(int i = 0; i < 32; i++){
        adc_input = adc1_get_raw(ADC_CHANNEL_4);
        adc_raw_read += adc_input;
    }
    adc_sampled = adc_raw_read / 32;
    //Converting data
    adc_conv_data = (adc_sampled * 2450) / 4095;

    return adc_conv_data;
}