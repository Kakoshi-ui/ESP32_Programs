#include <stdio.h>
#include "i2c_cfg.h"

void app_main(void){

    init_i2c();
    lcd_i2c_init();
    lcd_i2c_clear();

    lcd_set_pos(0,0);
    lcd_i2c_wr_string("Hola mundo");
}
