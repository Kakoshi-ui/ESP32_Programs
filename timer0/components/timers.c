#include <stdio.h>
#include "driver/gpio.h"
#include "driver/timer.h"
#include "timers.h"

volatile uint8_t count_value = 2;
volatile uint8_t led_state = 1;

void IRAM_ATTR timer0_callback(void *args){

    if(count_value == 0){

        gpio_set_level(GPIO_NUM_2,led_state);
        led_state = !led_state;
        count_value = 2;
    }

    else{
        count_value--;
    }

}

void init_timer0(void){

    uint8_t group = 0;
    uint8_t timer = 0;

    timer_config_t timer0_config = {
        .divider = 40000,              //This value sets the divider value factor to the clk_f, we are using the CPU_CLK that is 80Mhz
                                       // The divider factor is from 2-65536. Divider factor set to 40k to obtain a 2KHz frecuency
        .counter_dir = TIMER_COUNT_DOWN,
        .counter_en = TIMER_START,
        .alarm_en = TIMER_ALARM_EN,
        .auto_reload = TIMER_AUTORELOAD_EN,
        .intr_type = TIMER_INTR_LEVEL, 
    };

    //Inits the timer 0
    timer_init(group,timer, &timer0_config);

    //Seting up the timer counter value and alarm value
    timer_set_counter_value(group,timer,20000);
    timer_set_alarm_value(group,timer,0);

    //Sets the interrupt service routine settings
    timer_enable_intr(group,timer);
    timer_isr_callback_add(group,timer,timer0_callback,NULL,0);

 
}
