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
 
static int priority = 5;
xTaskHandle timer_task_handle;

void timer_task(void *pvParameter)
{
    while(true){
        vTaskDelay(3000 / portTICK_RATE_MS);
        printf("Weer 3 seconden\n");
        vTaskDelay(3000 / portTICK_RATE_MS);
        printf("Weer 3 seconden\n");
        priority--;
    
        if(priority == 1){
            vTaskDelete(timer_task_handle);
        } else {
            vTaskPrioritySet(timer_task_handle, priority);
        }
    }
}
 
void app_main()
{
    nvs_flash_init();
    xTaskCreate(&timer_task, "timer_task", 2048, NULL, 5, timer_task_handle);
}