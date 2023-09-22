#include <stdio.h>
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_log.h"
#include "set_adc.h"

#define SAMPLES 32

static const char *TAG = "ADC";
adc_oneshot_unit_handle_t adc_handle;

static bool init_adc_calibration(adc_unit_t unit, adc_atten_t atten){
    
    adc_cali_handle_t handle = NULL;
    esp_err_t adc_cali_scheme;
    bool calibrated = false;
    adc_cali_scheme_ver_t adc_cal_ver = ADC_CALI_SCHEME_VER_CURVE_FITTING;

    if((adc_cali_scheme = adc_cali_check_scheme(&adc_cal_ver)) == ESP_OK){
        adc_cali_curve_fitting_config_t cali_config = {
            .unit_id = unit,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_12,
        };
        adc_cali_create_scheme_curve_fitting(&cali_config,&handle);
        calibrated = true;
    }
    else{
        calibrated = false;
    }
    return calibrated;
}

void confg_adc(void){
    //ADC Init
    adc_oneshot_unit_init_cfg_t oneshot_confg = {
        .unit_id = ADC_UNIT_1
    };
    adc_oneshot_new_unit(&oneshot_confg, &adc_handle);
    //ADC config
    adc_oneshot_chan_cfg_t config = {
        .atten = ADC_ATTEN_DB_2_5,
        .bitwidth = ADC_BITWIDTH_12
    };
    adc_oneshot_config_channel(adc_handle,ADC_CHANNEL_0,&config);
    //ADC Calibration
    bool adc_calibrated = init_adc_calibration(ADC_UNIT_1,ADC_ATTEN_DB_2_5);
    if(adc_calibrated == false){
        ESP_LOGE(TAG,"CAN'T CALIBRATE ADC");
    }else{
        ESP_LOGI(TAG,"ADC CALIBRATED");
    }
}

uint32_t adc_raw_data(void){
    volatile uint32_t data_r = 0;
    //data_r = adc_oneshot_read();
    return data_r;
}