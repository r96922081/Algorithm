#include "common.h"
#include "list.h"

list_node* new_list_node()
{
    list_node* ret = (list_node*)(my_malloc(sizeof(list_node)));
    memset(ret, 0, sizeof(list_node));
    return ret;
}

list_node* list_append(list* l, void* value)
{
    list_node* n = new_list_node();
    n->value = value;
    n->next = NULL;
    n->prev = NULL;

    if (l->head == NULL)
    {
        l->head = n;
        l->tail = n;
    }
    else
    {
        l->tail->next = n;
        n->prev = l->tail;
        l->tail = n;
    }


    return n;
}

void list_remove(list* l, list_node* node)
{
    if (l->head == l->tail && l->head == node)
    {
        l->head = NULL;
        l->tail = NULL;
    }
    else if (l->head == node)
    {
        if (l->head->next != NULL)
            l->head->next->prev = NULL;

        l->head = l->head->next;
    }
    else if (l->tail == node)
    {
        if (l->tail->prev != NULL)
            l->tail->prev->next = NULL;

        l->tail = l->tail->prev;
    }
    else
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
}


list_node* list_insert_after(struct list* l, struct list_node* n, void* v)
{
    list_node* new_n = new_list_node();
    new_n->value = v;

    if (n == l->tail)
    {
        l->tail->next = new_n;
        new_n->prev = l->tail;
        l->tail = new_n;
    }
    else
    {
        new_n->prev = n;
        new_n->next = n->next;
        n->next->prev = new_n;
        n->next = new_n;
    }
    return new_n;
}

list_node* list_insert_before(struct list* l, struct list_node* n, void* v)
{
    list_node* new_n = new_list_node();
    new_n->value = v;

    if (n == l->head)
    {
        l->head->prev = new_n;
        new_n->next = l->head;
        l->head = new_n;
    }
    else
    {
        new_n->next = n;
        new_n->prev = n->prev;
        n->prev->next = new_n;
        n->prev = new_n;
    }
    return new_n;
}

list* new_list()
{
    list* l = (list*)(my_malloc(sizeof(list)));
    l->head = NULL;
    l->tail = NULL;
    l->append = list_append;
    l->remove = list_remove;
    l->insert_after = list_insert_after;
    l->insert_before = list_insert_before;
    return l;
}
void delete_list(list* l)
{
    list_node* n = l->head;

    while (n != NULL)
    {
        list_node* prev_n = n;
        n = n->next;
        my_free(prev_n);
    }

    my_free(l);
}

void delete_list_and_pointer(list* l)
{
    for (list_node* n = l->head; n != NULL; n = n->next)
        my_free(n->value);

    delete_list(l);
}

void test_list()
{
    list_node* n1 = NULL;
    list_node* n2 = NULL;
    list_node* n3 = NULL;
    list_node* n4 = NULL;
    list* l = NULL;

    l = new_list();
    l->append(l, (void*)1);
    delete_list(l);

    l = new_list();
    l->append(l, (void*)my_malloc(1));
    delete_list_and_pointer(l);

    l = new_list();
    check2(l->head == NULL);
    n1 = l->append(l, (void*)1);
    n2 = l->append(l, (void*)21);
    check2(l->head == n1);
    l->remove(l, n1);
    my_free(n1);
    check2(l->head == n2);
    l->remove(l, n2);
    my_free(n2);
    check2(l->head == NULL);
    delete_list(l);

    l = new_list();
    check2(l->tail == NULL);
    n1 = l->append(l, (void*)1);
    check2(l->tail == n1);
    n2 = l->append(l, (void*)2);
    check2(l->tail == n2);
    l->remove(l, n2);
    my_free(n2);
    check2(l->tail == n1);
    l->remove(l, n1);
    my_free(n1);
    check2(l->tail == NULL);
    delete_list(l);

    l = new_list();
    n1 = l->append(l, (void*)1);
    n2 = l->append(l, (void*)2);
    n3 = l->insert_before(l, n2, (void*)2); // 1, 3, 2
    check2(n1->next == n3);
    check2(n3->prev == n1);
    check2(n3->next == n2);
    check2(n2->prev == n3);
    n4 = l->insert_before(l, n1, (void*)2); // 4, 1, 3, 2
    check2(l->head == n4);
    check2(n4->next == n1);
    check2(n1->prev == n4);
    delete_list(l);

    l = new_list();
    n1 = l->append(l, (void*)1);
    n2 = l->append(l, (void*)2);
    n3 = l->insert_after(l, n1, (void*)3); // 1, 3, 2
    check2(n1->next == n3);
    check2(n3->prev == n1);
    check2(n3->next == n2);
    check2(n2->prev == n3);
    n4 = l->insert_after(l, n2, (void*)4); //1, 3, 2, 4
    check2(l->tail == n4);
    check2(n4->prev == n2);
    check2(n2->next == n4);
    delete_list(l);
}