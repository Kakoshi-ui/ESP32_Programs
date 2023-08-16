#ifndef SET_GPTIMER_H_
#define SET_GPTIMER_H_
#include "esp_system.h"
#include "soc/timer_group_reg.h"
#include "soc/timer_group_struct.h"

//Register setup

#define TIMG0_T0CONFIG_REG ((volatile uint32_t *)0x3FF5F000)
#define TIMG0_T0_EN 31
#define TIMG0_T0_INCREASE 30
#define TIMG0_T0_AUTORELOAD 29
#define TIMG0_T0_DIVIDER 13
#define TIMG0_T0_EDGE_INT_EN 12
#define TIMG0_T0_LEVEL_INT_EN 11
#define TIMG0_T0_ALARM_EN 10

//First 32bits of the timer register

//Read Only Registers
#define TIMG0_T0LO_REG ((volatile uint32_t *)0x3FF35F004)
#define TIMG0_T0HI_REG ((volatile uint32_t *)0x3FF35F008)
#define TIMG0_T0UPDATE_REG ((volatile uint32_t *)0x3FF5F00C)
#define TIMG0_T0ALARMLO_REG ((volatile uint32_t *)0x3FF5F010)
#define TIMG0_T0ALARMHI_REG ((volatile uint32_t *)0x3FF5F014)
#define TIMG0_T0LOADLO_REG ((volatile uint32_t *)0x355F5018)
#define TIMG0_T0LOADHI_REG ((volatile uint32_t *)0x355F501C)
#define TIMG0_T0LOAD_REG ((volatile uint32_t *)0x355F5020)

//Timer Interrupt Registers
//Int enable register
#define TIMG0_T0_INT_ENA_REG ((volatile uint32_t *)0x3FF5F098)
#define TIMG0_T0_INT_T0_INT_ENA 0
#define TIMG0_T0_INT_T1_INT_ENA 1
#define TIMG0_T0_INT_WDT_INT_ENA 2

#define TIMG0_T0_INT_RAW_REG ((volatile uint32_t *)0x3FF5F09C)
#define TIMG0_T0_INT_T0_INT_RAW 0
#define TIMG0_T0_INT_T1_INT_RAW 1
#define TIMG0_T0_INT_WDT_INT_RAW 2

#define TIMG0_T0_INT_ST_REG ((volatile uint32_t *)0x3FF5F0A0)
#define TIMG0_T0_INT_T0_INT_ST 0
#define TIMG0_T0_INT_T1_INT_ST 1
#define TIMG0_T0_INT_WDT_INT_ST 2

#define TIMG0_T0_INT_CLR_REG ((volatile uint32_t *)0x3FF5F0A4)
#define TIMG0_T0_INT_T0_INT_CLR 0
#define TIMG0_T0_INT_T1_INT_CLR 1
#define TIMG0_T0_INT_WDT_INT_CLR 2

void init_timG0_T0(void);

#endif /*SET_GPTIMER_H_*/