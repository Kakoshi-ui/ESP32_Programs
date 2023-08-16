#ifndef INIT_WIFI_H
#define INIT_WIFI_H

#include <string.h>
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "init_wifi.h"

static void event_handler(void* arg,esp_event_base_t event_base,
                            int32_t event_id, void* event_data);
void wifi_init_sta(void);

#endif/*INIT_WIFI_H*/