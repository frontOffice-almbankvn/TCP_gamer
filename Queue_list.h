#pragma once
struct Queue;
struct Queue* createQueue(unsigned capacity);
int isFull(struct Queue* queue);
int isEmpty(struct Queue* queue);
void enqueue(struct Queue* queue, char* item);
char* dequeue(struct Queue* queue);
char* front(struct Queue* queue);
char* rear(struct Queue* queue);