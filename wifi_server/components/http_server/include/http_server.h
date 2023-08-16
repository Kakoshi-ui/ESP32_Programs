#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include <esp_http_server.h>
#include "http_server.h"

esp_err_t get_handler(voidhttpd_req_t *req);

#endif/*HTTP_SERVER_H*/