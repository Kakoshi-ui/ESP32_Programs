#include <stdio.h>
#include "driver/gpio.h"
#include "driver/timer.h"
#include "timers.h"
#include "ports.h"

void app_main(void){

    set_gpios();
    init_timer0();

}
