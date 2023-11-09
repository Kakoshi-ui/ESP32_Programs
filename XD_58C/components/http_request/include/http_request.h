#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <esp_err.h>

#define ESP_ERROR_HTTP_BASE                     0x40000
#define ESP_ERROR_HTTP_DNS_LOOKUP_FAILED        (ESP_ERROR_HTTP_BASE + 1)
#define ESP_ERROR_HTTP_FAILED_ALLOCATING_SOCKET (ESP_ERROR_HTTP_BASE + 2)
#define ESP_ERROR_HTTP_SOCKET_CONNECT_FAIL      (ESP_ERROR_HTTP_BASE + 3)
#define ESP_ERROR_HTTP_SOCKET_SEND_FAILED       (ESP_ERROR_HTTP_BASE + 4)

//void http_client_request(const char* web_server, char* post_field);
esp_err_t http_client_request(const char *web_server, const char *request_string);

#endif/*HTTP_REQUEST_H*/
