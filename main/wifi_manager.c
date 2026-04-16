#include "wifi_manager.h"

 //wifi station mode example
static const char *TAG_STATION = "wifi_station";

void wifi_station_mode_example(void)
{
    // Initialize NVS flash (required for WiFi credentials storage)
    nvs_flash_init();

    // Initialize TCP/IP stack (required for WiFi functionality)
    esp_netif_init();

    // Create default event loop (required for WiFi event handling)
    esp_event_loop_create_default();

    // Create default WiFi station (STA) network interface
    esp_netif_create_default_wifi_sta();

    // Initialize WiFi with default configuration
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    // Configure WiFi connection settings (SSID and password)
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS
        },
    };

    // Set WiFi mode to station (STA)
    esp_wifi_set_mode(WIFI_MODE_STA);

    // Set WiFi configuration for station interface
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);

    // Start WiFi interface
    esp_wifi_start();

    // Connect to the configured WiFi network
    esp_wifi_connect();

    ESP_LOGI(TAG_STATION, "WiFi station started");
}

//wifi event example
static const char *TAG_EVENT = "wifi_event";
// WiFi event handler function
static void wifi_event_handler(void* arg,
                               esp_event_base_t event_base,
                               int32_t event_id,
                               void* event_data)
{
    // Handle different WiFi events based on event base and event ID
    if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        ESP_LOGI(TAG_EVENT,"WiFi Started");
        esp_wifi_connect();
    }

    if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_CONNECTED)
    {
        ESP_LOGI(TAG_EVENT,"Connected to Router");
    }

    if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        ESP_LOGI(TAG_EVENT,"Disconnected from Router");
    }
}

void wifi_event_example(void)
{
    // Initialize NVS flash (required for WiFi credentials storage)
    nvs_flash_init();

    // Initialize TCP/IP stack (required for WiFi functionality)
    esp_netif_init();

    // Create default event loop (required for WiFi event handling)
    esp_event_loop_create_default();

    // Create default WiFi station (STA) network interface
    esp_netif_create_default_wifi_sta();
    // Initialize WiFi with default configuration
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    esp_wifi_init(&cfg);

    esp_event_handler_instance_register(
        WIFI_EVENT,
        ESP_EVENT_ANY_ID,
        &wifi_event_handler,
        NULL,
        NULL
    );

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS
        },
    };

    esp_wifi_set_mode(WIFI_MODE_STA);

    esp_wifi_set_config(WIFI_IF_STA,&wifi_config);

    esp_wifi_start();
}


//wifi reconnect example

static const char *TAG_RECONNECT = "wifi_reconnect";

static int retry_count = 0;

static void wifi_reconnect_handler(void* arg,
                               esp_event_base_t event_base,
                               int32_t event_id,
                               void* event_data)
{
    if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        esp_wifi_connect();
    }

    else if(event_base == WIFI_EVENT &&
            event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        if(retry_count < 5)
        {
            esp_wifi_connect();
            retry_count++;

            ESP_LOGI(TAG_RECONNECT,"Retry connecting...");
        }
        else
        {
            ESP_LOGI(TAG_RECONNECT,"Connection failed");
        }
    }
}

void wifi_reconnect_example(void)
{
    nvs_flash_init();

    esp_netif_init();

    esp_event_loop_create_default();

    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    esp_wifi_init(&cfg);

    esp_event_handler_instance_register(
        WIFI_EVENT,
        ESP_EVENT_ANY_ID,
        &wifi_event_handler,
        NULL,
        NULL
    );

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS
        },
    };

    esp_wifi_set_mode(WIFI_MODE_STA);

    esp_wifi_set_config(WIFI_IF_STA,&wifi_config);

    esp_wifi_start();
}


//wifi network monitor example
static const char *TAG_MONITOR = "wifi_monitor";

void wifi_network_monitor(void)
{
    nvs_flash_init();

    esp_netif_init();

    esp_event_loop_create_default();

    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    esp_wifi_init(&cfg);

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS
        },
    };

    esp_wifi_set_mode(WIFI_MODE_STA);

    esp_wifi_set_config(WIFI_IF_STA,&wifi_config);

    esp_wifi_start();

    esp_wifi_connect();

    wifi_ap_record_t ap_info;

    if(esp_wifi_sta_get_ap_info(&ap_info) == ESP_OK)
    {
        ESP_LOGI(TAG_MONITOR,"Connected SSID: %s", ap_info.ssid);

        ESP_LOGI(TAG_MONITOR,"Signal Strength: %d", ap_info.rssi);
    }
}

 // TCP client example

 void wifi_init(void)
{
    printf("WiFi Init Called\n");
}
void tcp_client_test()
{
    struct sockaddr_in server_addr;
    int sock;
    char recv_buf[100];

    server_addr.sin_addr.s_addr = inet_addr("93.184.216.34"); 
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);

    sock = socket(AF_INET , SOCK_STREAM , 0);

    if(sock < 0)
    {
        printf("Socket creation failed\n");
        return;
    }

    printf("Socket created\n");

    if(connect(sock , (struct sockaddr*)&server_addr , sizeof(server_addr)) != 0)
    {
        printf("Connection failed\n");
        close(sock);
        return;
    }

    printf("Connected to server\n");

    char *request = "GET / HTTP/1.1\r\nHost: example.com\r\n\r\n";

    send(sock , request , strlen(request) , 0);

    int len = recv(sock , recv_buf , sizeof(recv_buf)-1 , 0);

    if(len > 0)
    {
        recv_buf[len] = 0;
        printf("Received Data:\n%s\n", recv_buf);
    }

    close(sock);
}