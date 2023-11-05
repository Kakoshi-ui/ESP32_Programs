idf_component_register(SRCS "thingspeak.c"
                    INCLUDE_DIRS "include"
                    REQUIRES "esp_http_client"
                    REQUIRES "mbedtls"
                    REQUIRES "esp-tls"
                    REQUIRES "http_request")
