#pragma once
#include "my_c_lib.h"

typedef struct stack {
    list* list;
    void (*push)(struct stack* s, void* value);
    void* (*pop)(struct stack* s);
    void* (*top)(struct stack* s);
    enum bool (*empty)(struct stack* s);
    void(*print)(struct stack* s);
}stack;

stack* new_stack();
void delete_stack(stack* s);
void delete_stack_and_pointer(stack* s);

typedef struct stack_int {
    stack* _s;
    void(*push)(struct stack_int* s, int value);
    int (*pop)(struct stack_int* s);
    int (*top)(struct stack_int* s);
    enum bool (*empty)(struct stack_int* s);
    void(*print)(struct stack_int* s);
}stack_int;

stack_int* new_stack_int();
void delete_stack_int(stack_int* s);