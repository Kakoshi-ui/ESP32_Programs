#include <stdio.h>
#include <string.h>
#include "wifi_sta.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

#define WIFI_SSID "Totalplay-65E4"
#define WIFI_PASS "65E451CCN42GNK43"
#define ESP_MAX_RETRY 10

#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_PSK

static EventGroupHandle_t s_wifi_event_group;

#define WIFI_CONNECTED_BIT  0x01
#define WIFI_FAIL_BIT       0x02

static const char *TAG = "ESP WIFI";

static int s_retry_num = 0;

static void event_handler(void* arg, esp_event_base_t event_base,
                            int32_t event_id, void* event_data){

    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START){
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED){
        if(s_retry_num < ESP_MAX_RETRY){
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG,"RETRYING TO CONNECT TO AP");
        }
        else{
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG,"FAILED CONNECTING TO AP");
    } else if(event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP){
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG,"GOT IP:"IPSTR,IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group,WIFI_CONNECTED_BIT);
    }
}

void wifi_init_sta(void){

    s_wifi_event_group = xEventGroupCreate();
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;

    esp_event_handler_instance_register(WIFI_EVENT,ESP_EVENT_ANY_ID,
                                        &event_handler,NULL,&instance_any_id);
    esp_event_handler_instance_register(IP_EVENT,IP_EVENT_STA_GOT_IP,
                                        &event_handler,NULL,&instance_got_ip);

    wifi_config_t wifi_config = {
        .sta = {
            .ssid       = WIFI_SSID,
            .password   = WIFI_PASS,
            .threshold.authmode = ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD,
            .sae_pwe_h2e = WPA3_SAE_PWE_BOTH,
        },
    };
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    esp_wifi_start();

    ESP_LOGI(TAG,"wifi_init_sta FINISHED");

    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                            WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                            pdFALSE,pdFALSE,portMAX_DELAY);
    if(bits & WIFI_CONNECTED_BIT){
        ESP_LOGI(TAG,"CONNECTED TO AP:%s PASSWORD:%s",WIFI_SSID,WIFI_PASS);
    } else if(bits & WIFI_FAIL_BIT){
        ESP_LOGI(TAG, "FAILED TO CONNECT TO AP");
    } else{
        ESP_LOGE(TAG,"UNEXPECTED_EVENT");
    }

    esp_event_handler_instance_unregister(IP_EVENT,IP_EVENT_STA_GOT_IP,instance_got_ip);
    esp_event_handler_instance_unregister(WIFI_EVENT,ESP_EVENT_ANY_ID,instance_any_id);
    vEventGroupDelete(s_wifi_event_group);
}