#include "common.h"
#include "stack.h"

void stack_push(struct stack* s, void* value)
{
    if (s->sp == s->_capacity)
    {
        void** old_array = s->array;
        s->_capacity *= 2;
        s->array = (void**)(my_malloc(sizeof(void*) * s->_capacity));
        for (int i = 0; i < s->_capacity / 2; i++)
            s->array[i] = old_array[i];
        my_free(old_array);
    }

    s->array[s->sp] = value;
    s->sp++;
}

void* stack_pop(struct stack* s)
{
    if (s->empty(s))
        raise();

    s->sp--;

    return s->array[s->sp];
}

void* stack_top(struct stack* s)
{
    if (s->empty(s))
        raise();

    return s->array[s->sp - 1];
}

int stack_empty(struct stack* s)
{
    return s->sp == 0;
}

stack* new_stack()
{
    stack* s = (stack*)my_malloc(sizeof(stack));
    s->sp = 0;
    s->_capacity = 100;
    s->array = (void**)(my_malloc(sizeof(void*) * s->_capacity));
    s->push = stack_push;
    s->pop = stack_pop;
    s->top = stack_top;
    s->empty = stack_empty;

    return s;
}

void delete_stack(stack* s)
{
    my_free(s->array);
    my_free(s);
}

void delete_stack_and_pointer(stack* s)
{
    while (!s->empty(s))
        my_free(s->pop(s));

    delete_stack(s);
}

void test_stack()
{
    stack* s = new_stack();
    for (int i = 0; i < 1024; i++)
    {
        s->push(s, (void*)i);
        check2(s->top(s) == (void*)i);
    }
    delete_stack(s);

    s = new_stack();
    s->push(s, my_malloc(1));
    s->push(s, my_malloc(2));
    s->push(s, my_malloc(3));
    delete_stack_and_pointer(s);
}