#include <esp_system.h>
#include <esp_log.h>
#include <stdio.h>

static const char* TAG = "MAIN";

void app_main(void){
    while(1){
        printf("Hola mundo con printf()");
        ESP_LOGI(TAG, "Hola mundo con ESP_LOGI");
        ESP_LOGI(TAG, "Rebooting in\n");
        for(int i = 10; i >= 0; i--){
            ESP_LOGI(TAG, "......%i",i);
        }
    }
}
