#include "esp_system.h"
#include "gpio_ports.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void IRAM_ATTR gpio_isr(void* args){

    *GPIO_OUT_W1TS_REG |= (1 << GPIO_NUM_5);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    
}

void set_gpios (void){

    *GPIO_OUT_REG |= (1 << GPIO_NUM_5);
    *GPIO_IN_REG |= 
    *GPIO_STATUS_INTERRUPT |= (1 << GPIO_NUM_5)

}