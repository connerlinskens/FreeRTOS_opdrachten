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

typedef struct queue
{
    char *data;
    struct queue *next;
} Queue;

Queue* queue;
int bufferSize = 10;
int items = 0;
SemaphoreHandle_t queue_sem;

char* queue_front(Queue **q)
{
        if (*q == NULL)
                return NULL;
        
        // Store the head and data of the head of the queue
        Queue *first = *q;
        char *data = first->data;

        // Set the head of the queue to the second in the queue
        (*q) = (*q)->next;
        // Remove the head of the queue from the memory
        free(first);

        return data;
}

void queue_enqueue(Queue **q , char *data)
{
        // Create a new node for the queue
        Queue *newNode = (Queue*) malloc(sizeof(Queue));
        Queue *last = *q;

        // Initialise the new node
        newNode->data = data;
        newNode->next = NULL;

        // If the queue is empty, set the new node as the head
        if (*q == NULL)
        {
                *q = newNode;
                return;
        }

        // Iterate through the list until the last node in the queue
        while (last->next != NULL)
                last = last->next;
        
        // Set the next for the last node as the new node
        last->next = newNode;
}

void consumer_task(void *pvParameter){
    int i = *(int *)pvParameter;

    while(true){
        if(items > 0){
            xSemaphoreTake(queue_sem, portMAX_DELAY);
            queue_front(&queue);
            items--;
            printf("Consumer %d removed an item, Total items: %d\n", i, items);
            xSemaphoreGive(queue_sem);
        }
        vTaskDelay(100);
    }
}

void producer_task(void *pvParameter){
    int i = *(int *)pvParameter;

    while(true){
        if(items < bufferSize){
            xSemaphoreTake(queue_sem, portMAX_DELAY);
            char* item = "item";
            queue_enqueue(&queue, item);
            items++;
            printf("Producer %d added an item, Total items: %d\n", i, items);
            xSemaphoreGive(queue_sem);
        }
        vTaskDelay(100);
    }
}

void app_main()
{
    // Init semaphore
    queue_sem = xSemaphoreCreateMutex();

    for (int i = 0; i < 3; i++) {
        xTaskCreate(producer_task, "producer_task", 2048, &i, 5, NULL);
    }

    for (int i = 0; i < 2; i++) {
        xTaskCreate(consumer_task, "consumer_task", 2048, &i, 5, NULL);
    }
    
    nvs_flash_init();
}