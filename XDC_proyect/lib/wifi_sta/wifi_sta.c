#include <stdio.h>
#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/task.h>
#include <nvs_flash.h>
#include "wifi_sta.h"

static const char *TAG = "WIFI_STA";
static EventGroupHandle_t s_wifi_event_group;

static void event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data){
    int s_retry_num = 0;
    if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START){
        esp_wifi_connect();
    }else if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED){
        if(s_retry_num < MAXIMUM_RETRY){
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG, "retry to connecto to AP");
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG, "connect to te AP fail");
    }else if(event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP){
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "got ip: " IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

void init_nvs_flash(void){

    //Initilaise the NVS flash memory to save the wifi configuration
    esp_err_t flash_init;
    flash_init = nvs_flash_init();
    //if the nvs_flash has no free pages or a new version is found, the nvs flash is erased to save data
    if(flash_init == ESP_ERR_NVS_NO_FREE_PAGES || flash_init == ESP_ERR_NVS_NEW_VERSION_FOUND){
        ESP_ERROR_CHECK(nvs_flash_erase());
        flash_init = nvs_flash_init();
    }
    ESP_ERROR_CHECK(flash_init);
}

void init_lwip(void){
    //Initializing the light weight ip
    ESP_ERROR_CHECK(esp_netif_init());
}

void event_register(void){
    //creates a event loop
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    //set the event handler instance register in any wifi event and the ip event
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler,
                                                        NULL, &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler,
                                                        NULL, &instance_got_ip));
}

void wifi_driver_wifi_task(void){
    //Creates a network interface between WIFI driver and the TCP/IP stack
    esp_netif_create_default_wifi_sta();

    //WIFI driver task
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
}

void start_wifi(void){

    init_nvs_flash();
    init_lwip();
    wifi_driver_wifi_task();
    event_register();

    wifi_config_t wifi_cfg = {
        .sta = {
            .ssid = SSID,
            .password = PASS,
        }
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());
}
