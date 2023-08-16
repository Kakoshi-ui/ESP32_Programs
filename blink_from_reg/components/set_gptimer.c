#include "set_gptimer.h"
#include "esp_system.h"
#include "ports.h"
#include "soc/soc.h"
#include "esp_intr_alloc.h"
#include "driver/timer.h"

volatile uint8_t led_state = 0; 
volatile uint16_t count = 1000;

void IRAM_ATTR timg0_t0_isr(void* args){
    if (count == 0){
        led_state ^= led_state;
        if(led_state == 1){
            *GPIO_OUT_W1TS_REG |= (1 << GPIO_NUMBER_5);
            count = 1000;
        }
        else{
            *GPIO_OUT_W1TC_REG |= (1 << GPIO_NUMBER_5);
        }
    }
    else{
        count--;
    }
    *TIMG0_T0_INT_CLR_REG |= (1 << TIMG0_T0_INT_T0_INT_CLR);
}

void init_timG0_T0(void){
    //Timer Initialization: 
    /* In this case we are using the timer group 0, timer 0
     * TIMG0_T0_EN: Enable the timer 0 Function
     * TIMG0_T0_INCREASE: Set if the timer counting is ascendent(set) or descendent(clear)
     * TIMG0_T0_AUTORELOAD: Make the timer autoreaload its count automatically
     * TIMG0_T0_DIVIDER: Preescaler value for the timer to 0xFFFF
     * 
     */
    *TIMG0_T0CONFIG_REG |= (1 << TIMG0_T0_AUTORELOAD);
    *TIMG0_T0CONFIG_REG  = (0x9C40 << TIMG0_T0_DIVIDER);
    *TIMG0_T0CONFIG_REG |= (1 << TIMG0_T0_LEVEL_INT_EN) | (1 << TIMG0_T0_ALARM_EN);
    //Timer0 Prescaler value defined in 20, Q2W356780P'´+}78+Z000, obtaining a F=200kHz; Remember F_CPU=40MHz

    //T0LOADLO_REG: Is the initial value of the counter, setup in 0
    *TIMG0_T0LOADLO_REG = 0x00030D40;
    *TIMG0_T0LOADHI_REG = 0x00000000;
    //T0ALARMLO_REG: Is the alarm value to launch the interrupt to the system
    *TIMG0_T0ALARMLO_REG = 0x00000000;
    *TIMG0_T0ALARMHI_REG = 0x00000000;
    //Reload value for the timer
    //*TIMG0_T0LOAD_REG = 0x00030D40;
    //Enable the interrupt flag when the timer is overflowing
    *TIMG0_T0_INT_ENA_REG |= (1 << TIMG0_T0_INT_T0_INT_ENA);

    //With all the setup ready, the next register enable and start the timer
    *TIMG0_T0CONFIG_REG |= (1 << TIMG0_T0_EN);

    //Enable the interrupt service routine
    esp_intr_alloc(ETS_TG0_T0_LEVEL_INTR_SOURCE, 0, timg0_t0_isr, NULL, NULL);

    if(((*TIMG0_T0CONFIG_REG) & (0x80000000)) == 0x80000000){
        *GPIO_OUT_W1TS_REG |= (1 << GPIO_NUMBER_2); 
    }
    else {
        *TIMG0_T0CONFIG_REG |= (1 << TIMG0_T0_EN);
    }
    
}