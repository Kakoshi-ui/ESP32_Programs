#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include <esp_http_server.h>
#include "http_server.h"

/*
 * Pasos para configurar el servidor http
 * 1ro: httpd_start(): crea una instancia del servidor http, aloja recursos/memoria 
 * para el servidor dependiendo sobre la configuracion y el manejo de salidas
 * El servidor tiene ambas: un socket sintonizador (TCP) para trafico HTTP 
 * y uno de control (UDP) para el control de señales
 * 
 * 2do: http_stop(): Detiene el servidor con el manejo proveido y libera los recursos/memoria
 * Esta es una funcion de bloqueo que primero señala detener las tareas del servidor y despues
 * espera a que termine la tarea
 * 
 * 3ro: httpd_register_uri_handler()
*/

//* Nuestra funcion de manejo de URI que sera llamada durante el GET/uri request
esp_err_t get_handler (httpd_req_t *req){

    const char resp[] = "URI GET Response";
    httpd_resp_send(req,resp,HTTPD_RESP_USE_STRLEN);

}
