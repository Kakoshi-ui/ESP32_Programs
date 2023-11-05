#ifndef WIFI_STA_H
#define WIFI_STA_H

#define SSID "INFINITUM0355_2.4"
#define PASS "eA7XpfMhJ4"
#define MAXIMUM_RETRY 5
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1

void wifi_init_sta(void);
void init_nvs_flash(void);

#endif/*WIFI_STA_H*/