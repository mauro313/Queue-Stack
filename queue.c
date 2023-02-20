#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/**
 * @brief create a new queue.
 * 
 * @param maxsize 
 * @return queue_t* 
 */
queue_t* queue_new(int maxsize){
  queue_t* new_queue = (queue_t*)malloc(sizeof(queue_t));
  if(new_queue == NULL){
    printf("memory cannot be reserved for a queue pointer");
    exit(EXIT_FAILURE); 
  }
  new_queue->a = (t_elem*)malloc(maxsize*sizeof(t_elem));
  if(new_queue->a == NULL){
    printf("memory cannot be reserved for a t_elem pointer");
    free(new_queue);
    exit(EXIT_FAILURE);      
  }
  new_queue->count = 0;
  new_queue->maxsize = maxsize;
  new_queue->head = 0;
  new_queue->tail = 0;
  return new_queue;      
}

/**
 * @brief free the memory of a queue.
 * 
 * @param q 
 */
void queue_free(queue_t** q){
  if(q != NULL && *q != NULL){
    free((*q)->a);
    (*q)->a = NULL;
    free(*q);
    *q = NULL;
  }
}

/**
 * @brief get the maxsize of a queue.
 * 
 * @param q 
 * @return int 
 */
int queue_getmaxsize(queue_t* q){ 
  if(q == NULL){
    printf("queue pointer is NULL(1)");
    exit(EXIT_FAILURE);      
  }
  return q->maxsize;        
}

/**
 * @brief get the current size of a queue.
 * 
 * @param q 
 * @return int 
 */
int queue_getsize(queue_t* q){
  if(q == NULL){
    printf("queue pointer is NULL(2)");
    exit(EXIT_FAILURE);     
  }
  return q->count;    
}

/**
 * @brief return true if a queue is full and false otherwise.
 * 
 * @param q 
 * @return true 
 * @return false 
 */
bool queue_isfull(queue_t* q){
  if(q == NULL){
    printf("queue pointer is NULL(3)");
    exit(EXIT_FAILURE);    
  }
  return (q->count == q->maxsize);    
}

/**
 * @brief return true if a queue is empty and false otherwise.
 * 
 * @param q 
 * @return true 
 * @return false 
 */
bool queue_isempty(queue_t* q){
  if(q == NULL){
    printf("queue pointer is NULL(4)");
    exit(EXIT_FAILURE);     
  }
  return (q->count == 0);
}

/**
 * @brief introduce an elment into a queue.Return true if the queue if the element was inserted and false 
 * otherwise(full queue).
 * 
 * @param q 
 * @param elem 
 * @return bool
 */
bool enqueue(queue_t* q, t_elem elem){
  if(q == NULL){
    printf("queue pointer is NULL(5)");
    exit(EXIT_FAILURE);     
  }
  bool returned = false;
  if(!queue_isfull(q)){
    q->a[q->tail] = elem;
    q->tail++;
    if(q->tail == q->maxsize){
      q->tail = 0;  
    }
    q->count++;
    returned = true;        
  }
  return returned;            
}

/**
 * @brief remove the first element of a queue.
 * 
 * @param q 
 * @return t_elem 
 */
t_elem dequeue(queue_t* q){
  if(q == NULL){
    printf("queue pointer is NULL(6)");
    exit(EXIT_FAILURE);   
  }
  if(queue_isempty(q)){
    printf("queue is empty(1)");
    exit(EXIT_FAILURE);  
  }
  t_elem returned = q->a[q->head];
  q->head++;
  if(q->head == q->maxsize){
    q->head = 0;  
  }
  q->count--;    
  return returned;
}

/**
 * @brief allows to see the first element of a queue.
 * 
 * @param q 
 * @return t_elem 
 */
t_elem peek(queue_t* q){
  if(q == NULL){
    printf("queue pointer is NULL(7)");
    exit(EXIT_FAILURE);   
  }
  if(queue_isempty(q)){
    printf("queue is empty(2)");
    exit(EXIT_FAILURE);  
  }
  return q->a[q->head];  
}

/**
 * @brief traverse a queue using a context variable.
 * 
 * @param queue 
 * @param queue_do 
 * @param context 
 */
void queue_traverse(queue_t* queue,bool queue_do(t_elem,void*),void* context){
  if(queue == NULL){
    printf("queue pointer is NULL(8)");
    return;   
  }  
  int counter = 0;
  while(counter<queue_getsize(queue) && queue_do(peek(queue),context)){
    t_elem auxiliar = dequeue(queue);
    enqueue(queue,auxiliar);
    counter++;  
  }
  while(counter<queue_getsize(queue)){
    enqueue(queue,dequeue(queue));  
  }
}


