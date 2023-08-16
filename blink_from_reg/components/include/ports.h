#ifndef PORTS_H_
#define PORTS_H_
#include "esp_system.h"
/*#include "soc/gpio_reg.h"
#include "soc/gpio_struct.h"*/

#define GPIO_ENABLE_REG ((volatile uint32_t *)0x3FF44020)
#define GPIO_OUT_W1TS_REG ((volatile uint32_t *)0x3FF44008)
#define GPIO_OUT_W1TC_REG ((volatile uint32_t *)0x3FF4400C)
#define GPIO_NUMBER_1 1 
#define GPIO_NUMBER_2 2
#define GPIO_NUMBER_5 5


void set_ports(void);

#endif/*PORTS_H_*/