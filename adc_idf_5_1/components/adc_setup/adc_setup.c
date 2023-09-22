#include <stdlib.h>
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_adc/adc_cali.h"
#include "esp_log.h"
#include "adc_setup.h"

#define EXAM_ATTEN ADC_ATTEN_DB_11
#define EXAM_BITWIDTH ADC_BITWIDTH_12
#define EXAM_UNIT ADC_UNIT_1
#define SAMPLES_NUM 32

static const char *TAG = "ADC";

static bool adc_calibration(adc_unit_t unit, adc_atten_t atten){
    
    /**
     * La funcion regresa un true en caso de que el adc esté calibrado despues de revisar la configuracion
     * y calibrar adecuadamente el adc
     */

    /* Hay dos esquemas de calibracion:
    ** - de ajuste de curva
    ** - de ajuste de linea
    ** La esp32s3 por defecto solo soporta el ajuste de curva, pero en caso de no saberlo es necesario buscar
    ** cual de los ajustes soporta
    */
    adc_cali_handle_t cali_handler = NULL;
    adc_cali_scheme_ver_t scheme_ver_curve = ADC_CALI_SCHEME_VER_CURVE_FITTING;
    esp_err_t cali_scheme_check;
    bool calibrated = false;

    if((cali_scheme_check = adc_cali_check_scheme(&scheme_ver_curve)) == ESP_OK){
        adc_cali_curve_fitting_config_t cali_confg = {
            .unit_id = unit,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_12,
        };
        adc_cali_create_scheme_curve_fitting(&cali_confg,&cali_handler);
        ESP_LOGI(TAG,"CALIBRATED (CURVE FITTING SCHEME)");
        calibrated = true;
    } 
    else {
        calibrated = false;
        ESP_LOGE(TAG, "IT WAS NOT POSSIBLE TO CALIBRATE ADC");
    }

    return calibrated;
}

void adc_config(adc_oneshot_unit_handle_t adc_handler){
    /**
     * Para configurar el adc existen algunos pasos que se deben seguir:
     * - Alojacion de recursos
     * 
     */
    bool adc_calibrated = false;
    if((adc_calibrated = adc_calibration(EXAM_UNIT,EXAM_ATTEN)) == true){
        /**
         * @param adc_handler: instancia del adc
         */
        // Configuracion de la unidad
        adc_oneshot_unit_init_cfg_t unit_confg = {
            .unit_id = ADC_UNIT_1,
            .clk_src = ADC_RTC_CLK_SRC_DEFAULT,
            .ulp_mode = ADC_ULP_MODE_DISABLE,
        };
        adc_oneshot_new_unit(&unit_confg,&adc_handler);

        // Configuracion del adc unidad 1 canal 0(GPIO )
        adc_oneshot_chan_cfg_t adc0_cfg ={
            .bitwidth = EXAM_BITWIDTH,
            .atten = EXAM_ATTEN,
        };
        adc_oneshot_config_channel(adc_handler,ADC_CHANNEL_0,&adc0_cfg);
        ESP_LOGI(TAG,"CONFIGURATED ADC FOR CHANNEL 0 UNIT 1");
    }
    else{
        ESP_LOGE(TAG,"ERROR. CANNOT INIT ADC BECAUSE IT IS NOT CALIBRATED");
    }
}

uint32_t adc_data(adc_oneshot_unit_handle_t adc_handler){
    volatile uint32_t data_r[32];
    volatile uint32_t data_buff = 0;
    volatile uint32_t data_s = 0;

    for(int i=0; i<SAMPLES_NUM ; i++){
        adc_oneshot_read(adc_handler,ADC_CHANNEL_0,&data_r);
        data_buff += data_r[i];
    }
    data_s = data_buff/SAMPLES_NUM;

    return data_s;
}
