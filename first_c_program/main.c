#include "esp_system.h"
#include "soc/gpio_reg.h"
//#include "freertos/FreeRTOS.h"
//#include "freertos/task.h"

#define GPIO_ENABLE_REG 0x3ff44020
#define GPIO_OUT_W1TS_REG 0x3ff44008
#define GPIO_2 2

void app_main(void){

    volatile uint32_t *enable_gpio = (volatile uint32_t *)GPIO_ENABLE_REG;
    volatile uint32_t *set_gpio = (volatile uint32_t *)GPIO_OUT_W1TS_REG;

    *enable_gpio |= (1 << GPIO_2);
    *set_gpio |= (1 << GPIO_2);



    /*REG_WRITE(GPIO_ENABLE_REG, 1 << GPIO_2);
    REG_WRITE(GPIO_OUT_W1TS_REG, 1 << GPIO_2);
    vTaskDelay(pdMS_TO_TICKS(1000));
    REG_WRITE(GPIO_OUT_W1TC_REG, 1 << GPIO_2);*/
}
