#include <stdio.h>
#include "esp_system.h"
#include "esp_http_client.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_event.h"
#include "esp_log.h"
#include "client_confg.h"

static const char *TAG = "HTTP CLIENT";

esp_err_t _http_event_handler(esp_http_client_event_t *evt){

    switch(evt->event_id){
        case HTTP_EVENT_ERROR:
            ESP_LOGI(TAG,"HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGI(TAG,"HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGI(TAG,"HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGI(TAG,"HTTP_EVENT_ON_HEADER");
            printf("%.*s",evt->data_len,(char*)evt->data);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGI(TAG,"HTTP_EVENT_ON_DATA, len=%d",evt->data_len);
            if (!esp_http_client_is_chunked_response(evt->client)){
                printf("%.*s",evt->data_len,(char*)evt->data);
            }
            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGI(TAG,"HTTP EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(TAG,"HTTP_EVENT_DISCONNECTED");
            break;
    }
    return ESP_OK;
}

void init_http_client(void){
    esp_http_client_config_t config = {
        .url = "",
        .event_handler = _http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);

    if(err == ESP_OK){
        ESP_LOGI(TAG,"Status = %d, content_length = %d",
                    esp_http_client_get_status_code(client),
                    esp_http_client_get_content_length(client));
    }
    esp_http_client_cleanup(client);
}
