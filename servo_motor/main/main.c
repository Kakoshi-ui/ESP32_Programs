#include <stdio.h>
#include "driver/gpio.h"
#include "pwm_setup.h"

void app_main(void){
    gpio_reset_pin(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_2,1);
    init_pwm();
}

