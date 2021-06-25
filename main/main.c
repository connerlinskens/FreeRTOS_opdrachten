#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

static const char* task1Text = "Task 1\n";
static const char* task2Text = "Task 2\n";
static const char* task3Text = "Task 3\n";
static const char* task4Text = "Task 4\n";
static const char* task5Text = "Task 5\n";
static const char* task6Text = "Task 6\n";
static const char* task7Text = "Task 7\n";
static const char* task8Text = "Task 8\n";
static const char* task9Text = "Task 9\n";
static const char* task10Text = "Task 10\n";
static const char* task11Text = "Task 11\n";
static const char* task12Text = "Task 12\n";
static const char* task13Text = "Task 13\n";
static const char* task14Text = "Task 14\n";
static const char* task15Text = "Task 15\n";
static const char* task16Text = "Task 16\n";
static const char* task17Text = "Task 17\n";
static const char* task18Text = "Task 18\n";
static const char* task19Text = "Task 19\n";
static const char* task20Text = "Task 20\n";


void task(void *pvParameter)
{
    char* taskName;
    taskName = (char*)pvParameter;
    
    while(true){
        printf(taskName);
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    nvs_flash_init();
    // Starting tasks dynamicly (doesnt work)
    // for (int i = 0; i < 20; i++)
    // {
    //     char buf[8];
    //     char* text = snprintf(buf, 8, "Task %d", i);
    //     xTaskCreate(&task, text, 2048, (void*)text, 5, NULL);
    // }

    xTaskCreate(&task, "Task 1", 2048, (void*)task1Text, 5, NULL);
    xTaskCreate(&task, "Task 2", 2048, (void*)task2Text, 5, NULL);
    xTaskCreate(&task, "Task 3", 2048, (void*)task3Text, 5, NULL);
    xTaskCreate(&task, "Task 4", 2048, (void*)task4Text, 5, NULL);
    xTaskCreate(&task, "Task 5", 2048, (void*)task5Text, 5, NULL);
    xTaskCreate(&task, "Task 6", 2048, (void*)task6Text, 5, NULL);
    xTaskCreate(&task, "Task 7", 2048, (void*)task7Text, 5, NULL);
    xTaskCreate(&task, "Task 8", 2048, (void*)task8Text, 5, NULL);
    xTaskCreate(&task, "Task 9", 2048, (void*)task9Text, 5, NULL);
    xTaskCreate(&task, "Task 10", 2048, (void*)task10Text, 5, NULL);
    xTaskCreate(&task, "Task 11", 2048, (void*)task11Text, 5, NULL);
    xTaskCreate(&task, "Task 12", 2048, (void*)task12Text, 5, NULL);
    xTaskCreate(&task, "Task 13", 2048, (void*)task13Text, 5, NULL);
    xTaskCreate(&task, "Task 14", 2048, (void*)task14Text, 5, NULL);
    xTaskCreate(&task, "Task 15", 2048, (void*)task15Text, 5, NULL);
    xTaskCreate(&task, "Task 16", 2048, (void*)task16Text, 5, NULL);
    xTaskCreate(&task, "Task 17", 2048, (void*)task17Text, 5, NULL);
    xTaskCreate(&task, "Task 18", 2048, (void*)task18Text, 5, NULL);
    xTaskCreate(&task, "Task 19", 2048, (void*)task19Text, 5, NULL);
    xTaskCreate(&task, "Task 20", 2048, (void*)task20Text, 5, NULL);

    

}