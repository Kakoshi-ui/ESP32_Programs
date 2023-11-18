#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "timers.h"
#include "ports.h"

void app_main(void){
    set_gpios();
    init_timer0();
}
