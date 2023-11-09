#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_system.h>
#include <esp_log.h>
#include <esp_http_client.h>

#include <lwip/err.h>
#include <lwip/sockets.h>
#include <lwip/sys.h>
#include <lwip/netdb.h>
#include <lwip/netif.h>
#include <lwip/dns.h>
#include "http_request.h"

static const char* TAG = "HTTP";

esp_err_t http_client_request(const char *web_server, const char *request_string){
    const struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
    };
    struct addrinfo *res;
    struct in_addr *addr;
    int s, r;
    char recv_buff[64];

    int err = getaddrinfo(web_server, "80", &hints, &res);
    
    if(err != 0 || res == NULL){
        ESP_LOGE(TAG,"DNS lookup failed err=%d res =%p",err,res);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        return ESP_ERROR_HTTP_DNS_LOOKUP_FAILED;
    }

    //Print the resolved IP:
    addr = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
    ESP_LOGI(TAG, "DNS look ip succeded. IP=%s",inet_ntoa(*addr));

    s = socket(res->ai_family, res->ai_socktype,0);
    if(s < 0){
        ESP_LOGE(TAG, "....Failed to allocate socket");
        freeaddrinfo(res);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        return ESP_ERROR_HTTP_FAILED_ALLOCATING_SOCKET;
    }
    ESP_LOGI(TAG, "....allocated socket");

    if(connect(s, res->ai_addr, res->ai_addrlen) != 0){
        ESP_LOGE(TAG, "....socket connect failed error_num = %d", errno);
        close(s);
        freeaddrinfo(res);
        vTaskDelay(4000/portTICK_PERIOD_MS);
        return ESP_ERROR_HTTP_SOCKET_CONNECT_FAIL;
    }
    ESP_LOGI(TAG, "....connected");
    freeaddrinfo(res);

    if(write(s, request_string, strlen(request_string)) < 0){
        ESP_LOGE(TAG, "....socket send failed");
        close(s);
        vTaskDelay(4000/portTICK_PERIOD_MS);
        return ESP_ERROR_HTTP_SOCKET_SEND_FAILED;
    }
    
    //Read HTTP response
    do{
        bzero(recv_buff, sizeof(recv_buff));
        r = read(s, recv_buff, sizeof(recv_buff)-1);
    }while(r > 0);
    ESP_LOGI(TAG, "....done reading from socket. Last read return=%d errno=%d", r, errno);
    close(s);
    return ESP_OK;
}

/*static const char* TAG = "HTTP";

void http_client_request(const char* web_server, char* post_field){
    esp_err_t error;

    esp_http_client_config_t client_cfg = {
        .url = web_server,
        .method = HTTP_METHOD_GET,
    };

    esp_http_client_handle_t client = esp_http_client_init(&client_cfg);
    esp_http_client_set_header(client, "Content-Type", "application/x-www-form-urlencoded");
    vTaskDelay(50/portTICK_PERIOD_MS);
    ESP_LOGI(TAG, "Field to post: %s", post_field);
    esp_http_client_set_post_field(client, post_field, strlen(post_field));

    error = esp_http_client_perform(client);
    if (error == ESP_OK){
        int status_code = esp_http_client_get_status_code(client);
        if(status_code == 200){
            ESP_LOGI(TAG, "Data Send Succesfully");
        }
        else{
            ESP_LOGE(TAG, "Data Send Error");
        }
    }
    else{
        ESP_LOGE(TAG, "Data Send Error");
    }
    esp_http_client_cleanup(client);
}*/