#include "esp_system.h"
#include "ports.h"

void set_ports(void){

    *GPIO_ENABLE_REG |= (1 << GPIO_NUMBER_1 ) | (1 << GPIO_NUMBER_2) | (1 << GPIO_NUMBER_5);
    *GPIO_OUT_W1TC_REG |= (1 << GPIO_NUMBER_5);

}