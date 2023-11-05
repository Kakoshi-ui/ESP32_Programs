#ifndef WIFI_STA_H
#define WIFI_STA_H

#include <freertos/event_groups.h>
#include <esp_system.h>
#include <esp_event.h>

#define SSID "INFINITUM0355_2.4"
#define PASS "eA7XpfMhJ4"
#define MAXIMUM_RETRY 15
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1

//static void event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
void init_nvs_flash(void);
void init_lwip(void);
void event_register(void);
void wifi_driver_wifi_task(void);
void start_wifi(void);

#endif/*WIFI_STA_H*/