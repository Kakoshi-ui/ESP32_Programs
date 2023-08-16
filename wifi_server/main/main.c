#include <stdio.h>
#include "nvs_flash.h"
#include "init_wifi.h"

void app_main(void){
    //* Wifi init as station -----------------------------------------------------------------------------
    esp_err_t ret = nvs_flash_init();
    if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND){
        nvs_flash_erase();
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    wifi_init_sta();
    //*---------------------------------------------------------------------------------------------------
}
