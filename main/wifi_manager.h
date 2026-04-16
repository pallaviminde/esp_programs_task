#ifndef WIFI_DRIVER_H          // Prevents multiple inclusion of this header file
#define WIFI_DRIVER_H     


#include "esp_wifi.h"        // WiFi driver functions and types
#include "esp_event.h"       // Event handling functions and types
#include "esp_log.h"        // ESP-IDF logging functions
#include "esp_netif.h"      // Network interface functions and types
#include "nvs_flash.h"      // Non-volatile storage functions (for WiFi credentials)
#include "lwip/sockets.h"     // Socket programming functions and types
#include "lwip/netdb.h"       // Network database functions (e.g., gethostbyname)

#define WIFI_SSID "V2036" // Replace with your WiFi SSID
#define WIFI_PASS "pallavi1232" // Replace with your WiFi password

/*
 * Function: wifi_station_mode_example
 * Demonstrates basic WiFi station (STA) mode setup.
 */
void wifi_station_mode_example(void);

/*
 * Function: wifi_event_example
 * Demonstrates handling of WiFi events
 * (connect, disconnect, IP acquisition, etc.).
 */
void wifi_event_example(void);

/*
 * Function: wifi_reconnect_example
 * Demonstrates WiFi auto-reconnection mechanism.
 */
void wifi_reconnect_example(void);

/*
 * Function: wifi_network_monitor
 * Monitors WiFi connection status and logs updates.
 */
void wifi_network_monitor(void);

/*
 * Function: wifi_init
 * Initializes WiFi system and connects to configured network.
 */
void wifi_init(void);

/*
 * Function: tcp_client_test
 * Demonstrates TCP client communication using sockets.
 * Example:
 * - Connect to server
 * - Send/receive data
 */
void tcp_client_test(void);

#endif // WIFI_DRIVER_H