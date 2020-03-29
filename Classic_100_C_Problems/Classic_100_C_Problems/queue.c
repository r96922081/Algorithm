#include "common.h"
#include "queue.h"

void queue_enqueue(struct queue* s, void* value)
{
    s->_list->append(s->_list, value);
}

void* queue_dequeue(struct queue* s)
{
    void* ret_value = s->_list->head->value;
    void* node = s->_list->head;

    s->_list->remove(s->_list, node);

    my_free(node);

    return ret_value;
}

void* queue_front(struct queue* s)
{
    return s->_list->head->value;
}

int queue_empty(struct queue* s)
{
    return s->_list->head == NULL;
}

queue* new_queue()
{
    queue* q = (queue*)my_malloc(sizeof(queue));
    q->_list = new_list();
    q->enqueue = queue_enqueue;
    q->dequeue = queue_dequeue;
    q->front = queue_front;
    q->empty = queue_empty;

    return q;
}

void delete_queue(queue* q)
{
    delete_list(q->_list);
    my_free(q);
}

void delete_queue_and_pointer(queue* q)
{
    while (!q->empty(q))
        my_free(q->dequeue(q));

    delete_queue(q);
}

void test_queue()
{
    queue* q = new_queue();
    for (int i = 0; i < 1024; i++)
        q->enqueue(q, (void*)i);

    for (int i = 0; i < 1024; i++)
    {
        check2(q->dequeue(q) == (void*)i);
    }

    delete_queue(q);

    q = new_queue();
    q->enqueue(q, my_malloc(1));
    q->enqueue(q, my_malloc(2));
    delete_queue_and_pointer(q);
}