#ifndef SET_ADC_H
#define SET_ADC_H

#include <stdio.h>
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_log.h"

static bool init_adc_calibration(adc_unit_t unit, adc_atten_t atten);
void confg_adc(void);
uint32_t adc_raw_data(void);

#endif/*SET_ADC_H*/