#ifndef GPIO_LEDS_H
#define GPIO_LEDS_H

void configure_gpio(uint8_t gpio_num);
void led_state(uint8_t gpio_num, uint8_t state);

#endif/*GPIO_LEDS_H*/