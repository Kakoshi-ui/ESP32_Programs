#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/mcpwm_types.h"
#include "driver/ledc.h"
#include "mcpwm_setup.h"

/* 
 * ESP32 offers two modes of PWM, one to control led instensity
 * and other to control electric motors, in this example we are using the 
 * MCPWM api to control a motor 
 */

void set_mcpw_drive(void){

    

}
