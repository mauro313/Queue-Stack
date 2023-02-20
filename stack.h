#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <stdbool.h>
#define t_elem void*

typedef struct{
  t_elem* s;
  int top;
  int maxsize;
}stack_t;

stack_t* stack_new(int maxsize);

void stack_free(stack_t** s);

int stack_getsize(stack_t* s);

int stack_getmaxsize(stack_t* s);

bool stack_isempty(stack_t* s);

bool stack_isfull(stack_t* s);

bool push(stack_t* s, t_elem elem);

t_elem pop(stack_t* s);

t_elem top(stack_t* s);

void stack_traverse(stack_t* stack,bool stack_do(t_elem,void*),void* context);

#include "stack.c"
#endif // STACK_H_INCLUDED
