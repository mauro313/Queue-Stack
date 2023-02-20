#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include <stdbool.h>
#define t_elem void*

typedef struct{
    t_elem* a;
    int head;   
    int tail;   
    int maxsize;
    int count;
}queue_t;

queue_t* queue_new(int maxsize);

void queue_free(queue_t** q);

int queue_getmaxsize(queue_t* q);

int queue_getsize(queue_t* q);

bool queue_isfull(queue_t* q);

bool queue_isempty(queue_t* q);

bool enqueue(queue_t* q, t_elem elem);

t_elem dequeue(queue_t* q);

t_elem peek(queue_t* q);

void queue_traverse(queue_t* queue,bool queue_do(t_elem,void*),void* context);

#include "queue.c"

#endif //QUEUE_H_INCLUDED