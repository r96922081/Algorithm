#pragma once
#include "common.h"

typedef struct queue {
    list* _list;
    void (*enqueue)(struct queue* s, void* value);
    void* (*dequeue)(struct queue* s);
    void* (*front)(struct queue* s);
    int(*empty)(struct queue* s);
}queue;

queue* new_queue();
void delete_queue(queue* s);
void delete_queue_and_pointer(queue* s);