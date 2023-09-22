#include <stdio.h>
#include "adc_setup.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"

void app_main(void){
    adc_oneshot_unit_handle_t adc_handler = NULL;    
    adc_config(adc_handler);

    volatile uint32_t data_from_adc = 0;
    data_from_adc = adc_data(adc_handler);
    
}
