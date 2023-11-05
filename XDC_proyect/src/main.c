#include <stdio.h>
#include <string.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include "wifi_sta.h"
#include "set_adc.h"
#include "thingspeak_snd_data.h"

//static const char *TAG = "main";

void app_main() {
    //Light up the gpio 2 led
    gpio_reset_pin(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_2, 1);

    //Starts all the drivers(adc, wifi)
    adc1_ch4_setup();
    start_wifi();
    vTaskDelay(1000/portTICK_PERIOD_MS);

    //int test_send = 0;
    float one_test = 1.0;

    http_set_url(one_test);
}