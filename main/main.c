#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "esp_spi_flash.h"
#include "freertos/timers.h"
#include "freertos/semphr.h"

#define NUM_OF_PHILOSOPHERS 5
#define MAX_NUMBER_ALLOWED (NUM_OF_PHILOSOPHERS - 1)
#define left(i) (i)
#define right(i) ((i + 1) % NUM_OF_PHILOSOPHERS)

SemaphoreHandle_t forks[NUM_OF_PHILOSOPHERS];
SemaphoreHandle_t philosophers_sem;
TaskHandle_t philosophers[NUM_OF_PHILOSOPHERS];

void think_task(void *pvParameter);

void take_fork(int i){
    TaskHandle_t think_task_handle = NULL;
    xTaskCreate(think_task, "think_task", 2048, &i, 2, &think_task_handle);

    xSemaphoreTake(forks[left(i)], portMAX_DELAY);
    xSemaphoreTake(forks[right(i)], portMAX_DELAY);

    vTaskDelete(think_task_handle);
}

void return_fork(int i){
    xSemaphoreGive(forks[left(i)]);
    xSemaphoreGive(forks[right(i)]);
    printf("Philosopher %d puts fork %d and %d back\n", i, left(i), right(i));
}

void think_task(void *pvParameter)
{
    int i = *(int *) pvParameter;
    while(1){
        printf("Philospher %d is thinking\n", i);
        vTaskDelay(500);
    }
}

void philosophers_task(void *pvParameter){
    int i = *(int *)pvParameter;
    while(true){
        xSemaphoreTake(philosophers_sem, portMAX_DELAY);

        take_fork(i);
        printf("Philosopher %d is eating\n", i);
        vTaskDelay(100 / portTICK_RATE_MS);
        return_fork(i);

        xSemaphoreGive(philosophers_sem);
        vTaskDelay(100 / portTICK_RATE_MS);
    }
}

void app_main()
{
    int param[NUM_OF_PHILOSOPHERS];

    for(int i = 0; i < NUM_OF_PHILOSOPHERS; i++){
        forks[i] = xSemaphoreCreateMutex();
    }

    philosophers_sem = xSemaphoreCreateCounting(MAX_NUMBER_ALLOWED, MAX_NUMBER_ALLOWED);

    for(int i = 0; i < NUM_OF_PHILOSOPHERS; i++){
        param[i] = i;
        xTaskCreate(philosophers_task, "philisophers_task", 2048, &param[i], 2, NULL);
    }
    nvs_flash_init();


}