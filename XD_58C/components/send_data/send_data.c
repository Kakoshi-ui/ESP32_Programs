#include <string.h>
#include "esp_system.h"
#include "esp_http_client.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_event.h"
#include "esp_log.h"
#include "send_data.h"

static const char *TAG = "SEND_DATA";

void thingspeak_send_data(void){
    char thingspeak_url[] = "https://api.thingspeak.com";
    char data[] = "/update?api_key=%s&field1=%d";
    char post_data[200];
    esp_err_t err;
}
