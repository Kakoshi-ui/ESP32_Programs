#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <esp_log.h>

static const char* TAG = "MAIN";

void IRAM_ATTR input_callback(void *args){
    gpio_set_level(GPIO_NUM_5, 1);
}

void app_main(void){
    gpio_set_direction(GPIO_NUM_5, GPIO_MODE_OUTPUT); //Set GPIOs 2 & 5 as outputs to ligth up 2 leds
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    //gpio_pad_select_gpio(GPIO_NUM_4);                   //Select and configure the GPIO 4 as input to recive the interrupt
    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_INPUT);
    gpio_set_intr_type(GPIO_NUM_4, GPIO_INTR_POSEDGE);  //Stablish a positive edge interrupt in GPIO 4

    gpio_install_isr_service(0);    //install the isr service
    gpio_isr_handler_add(GPIO_NUM_4, input_callback, NULL); //add the input callback function
    gpio_set_level(GPIO_NUM_2, 1);  //light on the GPIO 2 led
    ESP_LOGI(TAG, "Instaled ISR in GPIO_4");

    while (1){
        vTaskDelay(pdMS_TO_TICKS(5000)); //wait 5s to see the led on
        gpio_set_level(GPIO_NUM_5, 0);  //Reestablish the output to 0
    }
}
