// C program for array implementation of queue
#include "Queue_list.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A structure to represent a queue
struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
    char** thongdiep;
};

// function to create a queue
// of given capacity.
// It initializes size of queue as 0
struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(
        sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;

    // This is important, see the enqueue
    queue->rear = capacity - 1;
    //queue->array = (int*)malloc(
    //    queue->capacity * sizeof(int));
    queue->thongdiep = (char**)malloc(queue->capacity * sizeof(char*));
    return queue;
}

// Queue is full when size becomes
// equal to the capacity
int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, char* item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
        % queue->capacity;
    /*queue->array[queue->rear] = item;*/
    queue->thongdiep[queue->rear] = (char*)malloc(2048 * sizeof(char));
    strcpy(queue->thongdiep[queue->rear], item);
    queue->size = queue->size + 1;
    printf("%s enqueued to queue\n", item);
}

// Function to remove an item from queue.
// It changes front and size
char* dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    /*int item = queue->array[queue->front];*/
    char* item = queue->thongdiep[queue->front];
    queue->front = (queue->front + 1)
        % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Function to get front of queue
char* front(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    /*return queue->array[queue->front];*/
    return queue->thongdiep[queue->front];
}

// Function to get rear of queue
char* rear(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    /*return queue->array[queue->rear];*/
    return queue->thongdiep[queue->rear];
}

// Driver program to test above functions./
//int main()
//{
//    struct Queue* queue = createQueue(1000);
//
//    enqueue(queue, "10a");
//    enqueue(queue, "20b");
//    enqueue(queue, "30c");
//    enqueue(queue, "40d");
//
//    printf("%s dequeued from queue\n\n",
//        dequeue(queue));
//
//    printf("Front item is %s\n", front(queue));
//    printf("Rear item is %s\n", rear(queue));
//
//    return 0;
//}