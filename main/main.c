/* Hello World Example
 
   This example code is in the Public Domain (or CC0 licensed, at your option.)
 
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

#define RED_LED 4
#define GREEN_LED 2

void periodicTask_Red(void *pvParameter)
{
    int state = 0;

    gpio_pad_select_gpio(RED_LED);
    gpio_set_direction(RED_LED, GPIO_MODE_OUTPUT);
    gpio_set_level(RED_LED, state);

    portTickType xLastWakeTime;

    xLastWakeTime = xTaskGetTickCount();

    for(;;){
        state = state == 0? 1 : 0;
        gpio_set_level(RED_LED, state);
        vTaskDelayUntil(&xLastWakeTime, (1000 / portTICK_RATE_MS));
    }
}

void periodicTask_Green(void *pvParameter)
{
    int state = 0;

    gpio_pad_select_gpio(GREEN_LED);
    gpio_set_direction(GREEN_LED, GPIO_MODE_OUTPUT);
    gpio_set_level(GREEN_LED, state);

    portTickType xLastWakeTime;

    xLastWakeTime = xTaskGetTickCount();

    for(;;){
        state = state == 0? 1 : 0;
        gpio_set_level(GREEN_LED, state);
        vTaskDelayUntil(&xLastWakeTime, (200 / portTICK_RATE_MS));
    }
}
 
void app_main()
{
    nvs_flash_init();
    xTaskCreate(&periodicTask_Red, "periodicTask_Red", 2048, NULL, 5, NULL);
    xTaskCreate(&periodicTask_Green, "periodicTask_Green", 2048, NULL, 5, NULL);
}