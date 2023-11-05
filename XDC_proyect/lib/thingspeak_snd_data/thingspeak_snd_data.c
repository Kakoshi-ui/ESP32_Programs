#include <string.h>
#include <sdkconfig.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_http_client.h>
#include <esp_crt_bundle.h>
#include <esp_tls.h>
#include <esp_log.h>
#include "thingspeak_snd_data.h"

static const char *TAG = "ESP_HTTP";


void http_set_url(float adc_read){
    char thingspeak_url[] = "https://api.thingspeak.com";
    char data[] = "/update?api_key=%s&field1=%.2f";
    char api_key[] = "RPRQ9VR9G9L4AI0F";
    char post_data[200];
    //Configuring the http client protocol
    esp_http_client_config_t cfg = {
        .url = thingspeak_url,
        .method = HTTP_METHOD_GET,
        .transport_type = HTTP_TRANSPORT_OVER_TCP,
        .crt_bundle_attach = esp_crt_bundle_attach,
        .skip_cert_common_name_check = true
    };

    //client_handler instance is needed in all the http functions.
    esp_http_client_handle_t client_handler = esp_http_client_init(&cfg);
    esp_http_client_set_header(client_handler, "Content-Type", "application/x-www-form-urlencoded");

    //wait until 500ms
    vTaskDelay(500/portTICK_PERIOD_MS);

    //err: check if esp_http_client_perform() has done its work succesfully
    esp_err_t err;
    //clear the variable to send
    strcpy(post_data, "");
    //convert the (float)adc_read to string and joint it to the url part saved in DATA
    snprintf(post_data, sizeof(post_data), data, api_key, adc_read);
    ESP_LOGI(TAG, "url post data: %s", post_data);
    //set the http url
    esp_http_client_set_post_field(client_handler, post_data, strlen(post_data));
    //perform all the transfer call option
    err = esp_http_client_perform(client_handler);

    //evaluates the error message to verify if the data was succesfully sended
    if(err == ESP_OK){
        int status_code = esp_http_client_get_status_code(client_handler);
        if(status_code == 200){
            ESP_LOGI(TAG, "Message send succesfully");
        }
        else {
            ESP_LOGE(TAG, "Message send error");
        }
    } 
    else{
        ESP_LOGE(TAG, "Message send error");
    }
    //clean the http protocol/driver to be used in another instance
    esp_http_client_cleanup(client_handler);
}
