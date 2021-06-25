#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "esp_spi_flash.h"
#include "freertos/timers.h"
#include "freertos/semphr.h"


SemaphoreHandle_t writing;
SemaphoreHandle_t reading;
static int readCount = 0;
static char text[10];

void writer(void *pvParameter){
    int i = *(int *)pvParameter;
    vTaskDelay(10);

    char wr_text[10];
    sprintf(wr_text, "%d", i);

    while(true){
        xSemaphoreTake(writing, portMAX_DELAY);

        printf("Writer %d is writing\n", i);
        strcpy(text, wr_text);

        xSemaphoreGive(writing);
        vTaskDelay(100);
    }
}

void reader(void *pvParameter){
    while(true){
        // Lock readCount
        xSemaphoreTake(reading, portMAX_DELAY);
        readCount++;

        // Block writers
        if(readCount == 1)
            xSemaphoreTake(writing, portMAX_DELAY);

        // Unlock readCount
        xSemaphoreGive(reading);

        printf("Reader read: %s\n", text);

        // Lock readCount
        xSemaphoreTake(reading, portMAX_DELAY);
        readCount--;

        // Unblock writers
        if(readCount == 0)
            xSemaphoreGive(writing);

        // Unlock readCount
        xSemaphoreGive(reading);
        vTaskDelay(100);
    }
}



void app_main()
{
    // Init semaphores
    writing = xSemaphoreCreateBinary();
    xSemaphoreGive(writing);
    reading = xSemaphoreCreateBinary();
    xSemaphoreGive(reading);

    // Start reading and writing tasks
    for(int i = 0; i < 3; i++){
        xTaskCreate(writer, "writer", 2048, &(i), 5, NULL);
    }

    for(int i = 0; i < 3; i++){
        xTaskCreate(reader, "reader", 2048, NULL, 5, NULL);
    }

    nvs_flash_init();
}