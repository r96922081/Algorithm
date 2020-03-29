#include "common.h"
#include "stack.h"

void stack_push(struct stack* s, void* value)
{
    s->_list->append(s->_list, value);
}

void* stack_pop(struct stack* s)
{
    void* ret_value = s->_list->tail->value;
    void* node = s->_list->tail;

    s->_list->remove(s->_list, node);

    my_free(node);

    return ret_value;
}

void* stack_top(struct stack* s)
{
    return s->_list->tail->value;
}

int stack_empty(struct stack* s)
{
    return s->_list->head == NULL;
}

stack* new_stack()
{
    stack* s = (stack*)my_malloc(sizeof(stack));
    s->_list = new_list();
    s->push = stack_push;
    s->pop = stack_pop;
    s->top = stack_top;
    s->empty = stack_empty;

    return s;
}

void delete_stack(stack* s)
{
    delete_list(s->_list);
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