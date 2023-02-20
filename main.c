#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"
#include "stack.h"
#define size_1 20

queue_t* int_queue(int size);
void stack_destroy(stack_t** stck,void (*free_int)(int**));
void queue_destroy(queue_t** queue,void (*free_int)(int**));
void free_int(int** value);
void stack_printf(stack_t* stck,void (*print_int)(int*));
void queue_printf(queue_t* queue,int que_size,void (*print_int)(int*));
stack_t* remove_even(queue_t* queue);
void print_int(int* pointer);

int main(void){
  srand(time(NULL));
  queue_t* queue = int_queue(size_1);
  queue_printf(queue,queue_getsize(queue),print_int); 
  stack_t* stck = remove_even(queue);
  printf("\n\n");
  queue_printf(queue,queue_getsize(queue),print_int);
  printf("\n\n");
  stack_printf(stck,print_int);
  stack_destroy(&stck,free_int);
  queue_destroy(&queue,free_int);
  return 0;    
}

//******Ejemplo de uso de las implementaciones stack queue con estructuras estáticas***************************//

//creo una queue de 20 enteros y la imprimo
//creo una funcion que remueve los enteros pares de la queue y los devuelve en un stack
//imprimo la queue y el stack resultantes
//libero toda memoria utilizada

// funcion para crear una queue de enteros
queue_t* int_queue(int size){
  queue_t* new_queue = queue_new(size);
  int* pointer = NULL;
  while(!queue_isfull(new_queue)){
    pointer = (int*)malloc(sizeof(int));
    *pointer = rand()%100;
    enqueue(new_queue,pointer);
  }
  return new_queue; 
}

// remueve loe enteros pares y los devuelve en un stack
stack_t* remove_even(queue_t* queue){
  int size = queue_getsize(queue);
  stack_t* stck = stack_new(size);
  int counter = 0;
  while(counter < size){
    int* auxiliar = dequeue(queue);
    if((*auxiliar)%2 == 0){
      push(stck,auxiliar); 
    }
    else{
      enqueue(queue,auxiliar);
    }
    counter++;  
  }
  return stck;
}

// elimina el stack y su contenido
void stack_destroy(stack_t** stck,void (*free_int)(int**)){
  while(!stack_isempty(*stck)){
    int* auxiliar = pop(*stck);
    free_int(&auxiliar);  
  }
  stack_free(stck);
}

//elimina la queue y su contenido
void queue_destroy(queue_t** queue,void (*free_int)(int**)){
  while(!queue_isempty(*queue)){
    int* auxiliar = dequeue(*queue);
    free_int(&auxiliar);  
  }
  queue_free(queue);
}

// procedimientos para imprimir un stack y una queue
void stack_printf(stack_t* stck,void (*print_int)(int*)){
  if(!stack_isempty(stck)){
    int* auxiliar = pop(stck);
    stack_printf(stck,print_int);
    push(stck,auxiliar);
    print_int(auxiliar);
  }
}

void queue_printf(queue_t* queue,int que_size,void (*print_int)(int*)){
  if(que_size > 0){
    int* auxiliar = dequeue(queue);
    print_int(auxiliar);
    enqueue(queue,auxiliar);
    queue_printf(queue,que_size-1,print_int);  
  }  
}
////////////////////////////////////////


void print_int(int* pointer){
  printf("%i ",*pointer);  
}

void free_int(int** value){
  free(*value);
  *value = NULL;  
}