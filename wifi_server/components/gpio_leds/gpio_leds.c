#include <stdio.h>
#include "driver/gpio.h"
#include "gpio_leds.h"

void configure_gpio(uint8_t gpio_num){
    gpio_reset_pin(gpio_num);
    gpio_set_direction(gpio_num,GPIO_MODE_OUTPUT);
}

void led_state(uint8_t gpio_num,uint8_t state){

    gpio_set_level(gpio_num,state);

}
