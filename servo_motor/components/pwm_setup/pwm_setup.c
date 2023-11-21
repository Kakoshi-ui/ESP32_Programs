#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/ledc.h>
#include <esp_log.h>
#include "pwm_setup.h"

void init_pwm(void){
    ledc_timer_config_t tim_cfg = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_12_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 50,
        .clk_cfg = LEDC_USE_APB_CLK
    };

    ledc_timer_config(&tim_cfg);

    ledc_channel_config_t gpio_cfg = {
        .gpio_num = GPIO_NUM_12,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0x0000    //Max: 0x1000 min 0x0080
    };
    ledc_channel_config(&gpio_cfg);
}

void set_pwm_pos(uint16_t position){
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, position);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
}
