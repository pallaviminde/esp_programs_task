#ifndef WIFI_DRIVER_H
#define WIFI_DRIVER_H


#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "nvs_flash.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"

#define WIFI_SSID "V2036"
#define WIFI_PASS "pallavi1232"
void wifi_station_mode_example(void);
void wifi_event_example(void);
void wifi_reconnect_example(void);
void wifi_network_monitor(void);
void wifi_init(void);
void tcp_client_test(void);

#endif