#ifndef GPIO_PORTS_H_
#define GPIO_PORTS_H_
#include "esp_system.h"

//GPIO's definition
#define GPIO_NUM_1 1
#define GPIO_NUM_2 2
#define GPIO_NUM_3 3
#define GPIO_NUM_4 4
#define GPIO_NUM_5 5
#define GPIO_NUM_6 6
#define GPIO_NUM_7 7
#define GPIO_NUM_8 8
#define GPIO_NUM_9 9
#define GPIO_NUM_10 10

#define GPIO_OUT_REG ((volatile uint32_t *)0x3FF44004)
#define GPIO_OUT_W1TS_REG ((volatile uint32_t *)0x3FF44008)
#define GPIO_OUT_W1TC_REG ((volatile uint32_t *)0x3FF4400C)
#define GPIO_ENABLE_REG ((volatile uint32_t *)0x3FF44020)
#define GPIO_IN_REG ((volatile uint32_t *)0x3FF4403C)
#define GPIO_STATUS_W1TS_REG ((volatile uint32_t *)0x3FF44044)
#define GPIO_STATUS_W1TC_REG ((volatile uint32_t *)0x3FF4404C)
#define GPIO_STATUS_REG ((volatile uint32_t *)0x3FF44044)


#endif/*GPIO_PORTS_H_*/