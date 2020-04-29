#include "my_c_lib.h"
#include "stack.h"

void stack_push(struct stack* s, void* value)
{
    s->list->append(s->list, value);
}

void* stack_pop(struct stack* s)
{
    void* ret_value = s->list->tail->value;
    void* node = s->list->tail;

    s->list->remove(s->list, node);

    my_free(node);

    return ret_value;
}

void* stack_top(struct stack* s)
{
    return s->list->tail->value;
}

bool stack_empty(struct stack* s)
{
    return s->list->head == NULL;
}

void stack_print(struct stack* s)
{
    s->list->print(s->list);
}

stack* new_stack()
{
    stack* s = (stack*)my_malloc(sizeof(stack));
    s->list = new_list();
    s->push = stack_push;
    s->pop = stack_pop;
    s->top = stack_top;
    s->empty = stack_empty;
    s->print = stack_print;

    return s;
}

void delete_stack(stack* s)
{
    delete_list(s->list);
    my_free(s);
}

void delete_stack_and_pointer(stack* s)
{
    while (!s->empty(s))
        my_free(s->pop(s));

    delete_stack(s);
}

void stack_int_push(struct stack_int* s, int value)
{
    s->_s->push(s->_s, (void*)value);
}

int stack_int_pop(struct stack_int* s)
{
    return (int)s->_s->pop(s->_s);
}

int stack_int_top(struct stack_int* s)
{
    return (int)s->_s->top(s->_s);
}

bool stack_int_empty(struct stack_int* s)
{
    return s->_s->empty(s->_s);
}

void stack_int_print(struct stack_int* s)
{
    s->_s->print(s->_s);
}

stack_int* new_stack_int()
{
    stack_int* s = (stack_int*)my_malloc(sizeof(stack_int));
    s->_s = new_stack();
    s->push = stack_int_push;
    s->pop = stack_int_pop;
    s->top = stack_int_top;
    s->empty = stack_int_empty;
    s->print = stack_int_print;

    return s;
}

void delete_stack_int(stack_int* s)
{
    delete_stack(s->_s);
    my_free(s);
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