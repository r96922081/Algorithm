#pragma once

typedef struct stack {
    int sp;
    int _capacity;
    void** array;
    void(*push)(struct stack* s, void* value);
    void* (*pop)(struct stack* s);
    void* (*top)(struct stack* s);
    int (*empty)(struct stack* s);
    void(*clear)(struct stack* s);
}stack;

stack* new_stack();
void delete_stack(stack* s);
void delete_stack_and_pointer(stack* s);