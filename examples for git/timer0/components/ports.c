#include <stdio.h>
#include "driver/gpio.h"
#include "ports.h"

void set_gpios(void){

    gpio_reset_pin(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2,GPIO_MODE_OUTPUT);

}
