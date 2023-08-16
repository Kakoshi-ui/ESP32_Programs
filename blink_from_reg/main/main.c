#include <stdio.h>
#include "esp_system.h"
#include "set_gptimer.h"
#include "ports.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void){

    set_ports();
    init_timG0_T0();
    
}
