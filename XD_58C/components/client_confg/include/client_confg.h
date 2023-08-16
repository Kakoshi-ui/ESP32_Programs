#ifndef CLIENT_CONFG_H
#define CLIENT_CONFG_H

#include <stdio.h>
#include "esp_system.h"
#include "esp_http_client.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_event.h"
#include "esp_log.h"
#include "client_confg.h"

esp_err_t _http_event_handler(esp_http_client_event_t *evt);
void init_http_client(void);


#endif/*CLIENT_CONFG_H*/