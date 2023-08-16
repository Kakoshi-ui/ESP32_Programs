#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "pwm_setup.h"

void init_pwm(void){

    //* Timer setup, for the pwm mode
    ledc_timer_config_t tim_cfg = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_16_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 50,
        .clk_cfg = LEDC_USE_APB_CLK,
    };
    ledc_timer_config(&tim_cfg);

    //* PWM channel setup
    ledc_channel_config_t gpio_cfg = {
        .gpio_num = GPIO_NUM_12,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0x80
    };
    ledc_channel_config(&gpio_cfg);

}

