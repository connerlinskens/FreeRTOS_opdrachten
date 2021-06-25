#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

void task(void *pvParameter)
{
    int i = *(int *)pvParameter;
    
    while(true){
        printf("Task  %d\n", i);
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    nvs_flash_init();
    // Starting tasks dynamicly
    for (int i = 0; i < 20; i++)
    {
        xTaskCreate(&task, "task", 2048, &i, 5, NULL);
    }
}