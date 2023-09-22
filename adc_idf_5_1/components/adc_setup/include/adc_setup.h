#ifndef ADC_SETUP_H
#define ADC_SETUP_H

#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"

static bool adc_calibration(adc_unit_t unit, adc_atten_t atten);
void adc_config(adc_oneshot_unit_handle_t adc_handler);
uint32_t adc_data(adc_oneshot_unit_handle_t adc_handler);

#endif/*ADC_SETUP_H*/
