#include <stdio.h>
#include <string.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <esp_system.h>

#include "thingspeak.h"
#include "http_request.h"

#define WEB_SERVER "api.thingspeak.com"
#define WRITE_API_KEY "RPRQ9VR9G9L4AI0F"
#define THINGSPEAK_URL "https://api.thingspeak.com"
#define DATA "/update?api_key=RPRQ9VR9G9L4AI0F&field1="

static const char* get_request_start = "GET /update?key="WRITE_API_KEY;
static const char* get_request_end = 
    "HTTP/1.1\n"
    "Host: "WEB_SERVER"\n"
    "Connection: close\n"
    "User-Agent: esp32 / esp-idf\n"
    "\n";
static const char* TAG = "THINGSPEAK";

void thingSpeak_post_data(float value){
    int n = snprintf(NULL, 0, "%.2f", value);
    char field1[n+1];
    sprintf(field1, "%.2f", value);

    int string_size = strlen(get_request_start);
    string_size += strlen("&fieldN=");
    string_size += strlen(field1);
    string_size += (strlen(get_request_end)+1);

    char* post_data = malloc(string_size);
    strcpy(post_data, get_request_start);
    strcat(post_data, "&field1=");
    strcat(post_data, field1);
    strcat(post_data, get_request_end);

    esp_err_t err;
    err = http_client_request(WEB_SERVER, post_data);

    if (err != ESP_OK){
        ESP_LOGE(TAG, "Error posting DATA");
    }
    else{
        ESP_LOGI(TAG, "Succesfully sended DATA, DATA post: %s", post_data);
    }
    free(post_data);
}


/*static const char* TAG = "ThingSpeak";

void thingSpeak_post_data(float value){
    int n = snprintf(NULL, 0, "%.2f", value);
    char field1[n+1];
    sprintf(field1, "%.2f", value);

    int string_length = strlen(THINGSPEAK_URL);
    string_length += strlen(DATA);
    string_length += strlen(field1);

    char data_post[string_length+1];
    strcpy(data_post, THINGSPEAK_URL);
    strcat(data_post, DATA);
    strcat(data_post, field1);

    http_client_request(THINGSPEAK_URL, data_post);
}*/
