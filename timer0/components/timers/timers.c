#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <driver/gpio.h>
#include <esp_log.h>
#include "timers.h"

static const char* TAG = "TIMER";
TimerHandle_t xTimers;
int timerID = 1;
volatile uint8_t led_state = 0;

static void vTimerCallback(TimerHandle_t pxTimer){
    ESP_LOGI(TAG, "Event was called from timer");
    gpio_set_level(GPIO_NUM_2, led_state);
    led_state ^= 1;
}

void init_timer0(void){    
    ESP_LOGI(TAG, "Configurating Timer");
    xTimers = xTimerCreate( "Timer0",       // Just a text name, not used by the kernel.
                            (pdMS_TO_TICKS(2000)),   // The timer period in ticks.
                            pdTRUE,        // The timers will auto-reload themselves when they expire.
                            ( void * ) timerID,  // Assign each timer a unique id equal to its array index.
                            vTimerCallback // Each timer calls the same callback when it expires.
                            );
    
    if(xTimers == NULL){
        ESP_LOGE(TAG, "Timer was no initialized");
    }
    else{
        if(xTimerStart(xTimers,0) != pdPASS){
            ESP_LOGE(TAG, "Timer could not be in active mode");
        }
    }
}