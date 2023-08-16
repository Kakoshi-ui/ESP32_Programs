#ifndef SEND_DATA_H
#define SEND_DATA_H

#include <string.h>
#include "esp_system.h"
#include "esp_http_client.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_event.h"
#include "esp_log.h"

void thingspeak_send_data(void);

#endif/*SEND_DATA_H*/