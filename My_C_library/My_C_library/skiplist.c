#include "my_c_lib.h"
#include "skiplist.h"
#include "stdio.h"

typedef struct list_ext {
    struct list_node_ext* (*append)(struct list_ext*, void* key, void* v);
    void(*insert_after)(struct list_ext*, struct list_node_ext*, struct list_node_ext*);
    void(*insert_before)(struct list_ext*, struct list_node_ext*, struct list_node_ext*);
    void(*remove)(struct list_ext*, struct list_node_ext*);
    void(*clear)(struct list_ext*);
    struct list_node_ext* (*head)(struct list_ext*);
    struct list_node_ext* (*tail)(struct list_ext*);
    void(*print)(struct list_ext*);
    list* list;
}list_ext;

typedef struct list_node_ext {
    struct list_node_ext* next;
    struct list_node_ext* prev;
	struct list_node_ext* below;
    void* value;
    void* key;
}list_node_ext;

struct list_node_ext* list_ext_head(struct list_ext* l)
{
    return (struct list_node_ext*)(l->list->head);
}

struct list_node_ext* list_ext_tail(struct list_ext* l)
{
    return (struct list_node_ext*)(l->list->tail);
}

list_node_ext* list_ext_append(struct list_ext* l, void* key, void* v)
{
    list_node_ext* new_n = (list_node_ext*)my_malloc(sizeof(list_node_ext));
    new_n->next = NULL;
    new_n->prev = NULL;
    new_n->below = NULL;
    new_n->key = key;
    new_n->value = v;

    if (l->list->head == NULL)
    {
        l->list->head = (list_node*)new_n;
        l->list->tail = (list_node*)new_n;
    }
    else
    {
        l->list->insert_after_2(l->list, l->list->tail, (struct list_node*)new_n);
    }

    return new_n;
}

void list_ext_remove(struct list_ext* l, struct list_node_ext* n)
{
    l->list->remove(l->list, (struct list_node*)n);
}

void list_ext_insert_after(struct list_ext* l, struct list_node_ext* n, struct list_node_ext* new_n)
{
    l->list->insert_after_2(l->list, (struct list_node*)n, (struct list_node*)new_n);
}

void list_ext_insert_before(struct list_ext* l, struct list_node_ext* n, struct list_node_ext* new_n)
{
    l->list->insert_before_2(l->list, (struct list_node*)n, (struct list_node*)new_n);
}

void list_ext_list_clear(struct list_ext* l)
{
    l->list->clear(l->list);
}

void list_ext_print(struct list_ext* l)
{
    for (list_node_ext* n = l->head(l); n != NULL; n = n->next)
    {
        if (n != l->head(l))
            printf(", ");

        printf("(%d, %d)", (int)(n->key), (int)(n->value));
    }

    printf("\n");
}

list_ext* new_list_ext()
{
    list_ext* l = (list_ext*)(my_malloc(sizeof(list_ext)));
    l->list = new_list();
    l->head = list_ext_head;
    l->tail = list_ext_tail;
    l->append = list_ext_append;
    l->remove = list_ext_remove;
    l->insert_after = list_ext_insert_after;
    l->insert_before = list_ext_insert_before;
    l->clear = list_ext_list_clear;
    l->print = list_ext_print;
    return l;
}

void delete_list_ext(list_ext* l)
{
    delete_list(l->list);

    my_free(l);
}

vector* get_insert_after_nodes(list_ext* current_list, int key)
{
    list_node_ext* inserted_after_node = current_list->head(current_list);

    vector* inserted_after_node_vector = new_vector();

    while (inserted_after_node != NULL)
    {
        while (inserted_after_node->next != NULL && (int)inserted_after_node->next->key <= (int)key)
        {
            inserted_after_node = inserted_after_node->next;
        }

        if (inserted_after_node->prev != NULL && (int)inserted_after_node->key == (int)key)
        {
            delete_vector(inserted_after_node_vector);
            return NULL;
        }

        inserted_after_node_vector->append(inserted_after_node_vector, inserted_after_node);
        inserted_after_node = inserted_after_node->below;
    }

    return inserted_after_node_vector;
}

void insert_node(vector* inserted_after_node_vector, void* key, void* value)
{
    list_node_ext* prev_inserted = NULL;
    for (int i = 0; i < inserted_after_node_vector->size; i++)
    {
        list_node_ext* inserted_after_node = inserted_after_node_vector->at(inserted_after_node_vector, i);

        list_node_ext* new_n = (list_node_ext*)my_malloc(sizeof(list_node_ext));
        memset(new_n, 0, sizeof(list_node_ext));
        if (prev_inserted != NULL)
            prev_inserted->below = new_n;
        prev_inserted = new_n;
        new_n->key = key;
        new_n->value = value;

        new_n->next = inserted_after_node->next;
        new_n->prev = inserted_after_node;
        if (inserted_after_node->next != NULL)
            inserted_after_node->next->prev = new_n;
        inserted_after_node->next = new_n;
    }
}

bool skip_list_insert(struct skip_list* sl, void* key, void* value)
{
    list_node* level = sl->level_list->head;
    while (level != NULL && rand() % 2 == 0)
    {
        level = level->next;
    }

    bool new_current_list = false;
    list_ext* current_list = NULL;

    if (level == NULL)
    {
        current_list = new_list_ext();
        new_current_list = true;

        // dummy, never deleted
        list_node_ext* n = current_list->append(current_list, (void*)-1, (void*)-1);

        if (level == sl->level_list->head)
        {
            n->below = NULL;
        }
        else
        {
            list_ext* below_list = (list_ext*)sl->level_list->tail->value;
            n->below = (list_node_ext*)(below_list->head(below_list));
        }
    }
    else
    {
        current_list = (list_ext*)level->value;
    }

    vector* inserted_after_node_vector = get_insert_after_nodes(current_list, (int)key);

    if (inserted_after_node_vector == NULL)
    {
        if (new_current_list)
            delete_list_ext(current_list);
        
        return false;
    }

    insert_node(inserted_after_node_vector, key, value);

    delete_vector(inserted_after_node_vector);

    if (new_current_list)
        sl->level_list->append(sl->level_list, (void*)current_list);
    return true;
}

list_node_ext* skip_list_find_2(struct skip_list* sl, void* key)
{
	list_node* level_node = sl->level_list->tail;
	if (level_node == NULL)
		return NULL;

	list_ext* current_list = (list_ext*)(level_node->value);

	list_node_ext* current_node = current_list->head(current_list);

	while (current_node != NULL)
	{
		if (current_node->next == NULL || current_node->next->key > key)
		{
			current_node = current_node->below;
		}
		else if ((int)current_node->next->key == (int)key)
		{
			return current_node->next;
		}
		else
		{
			current_node = current_node->next;
		}
	}

	return NULL;
}

bool skip_list_find(struct skip_list* sl, void* key, void** value)
{
	list_node_ext* n = skip_list_find_2(sl, key);

	if (n == NULL)
		return false;
	else
	{
		*value = n->value;
		return true;
	}
}

bool skip_list_delete(struct skip_list* sl, void* key)
{
	list_node_ext* n = skip_list_find_2(sl, key);

	if (n == NULL)
		return false;


	while (n != NULL)
	{
		n->prev->next = n->next;
		if (n->next != NULL)
			n->next->prev = n->prev;

		list_node_ext* next_n = n->below;

		// this level has only 1 node, and should be deleted
		if (n->prev->prev == NULL && n->next == NULL)
		{
			list* l = sl->level_list;
			delete_list_ext((list_ext*)(l->tail->value));
			list_node* tail = l->tail;
			l->remove(l, tail);
			my_free(tail);
		}

		my_free(n);

		n = next_n;
	}


	return true;
}

void skip_list_print(struct skip_list* sk)
{
    for (list_node* n = sk->level_list->tail; n != NULL; n = n->prev)
    {
        list_ext* l = (list_ext*)n->value;
        for (list_node_ext* n2 = l->head(l)->next; n2 != NULL; n2 = n2->next)
        {
            if (n2 != l->head(l)->next)
                printf(", ");
            printf("%d", (int)n2->key);
        }
        printf("\n");
    }
}

skip_list* new_skip_list()
{
    skip_list* sl = (skip_list *)(my_malloc(sizeof(skip_list)));
    sl->level_list = new_list();
    sl->insert = skip_list_insert;
	sl->find = skip_list_find;
	sl->delete = skip_list_delete;
    sl->print = skip_list_print;

    return sl;
}

void delete_skip_list(skip_list* sl)
{
    for (list_node* level = sl->level_list->head; level != NULL; level = level->next)
    {
        list_ext* l = level->value;
        delete_list_ext(l);
    }

    delete_list(sl->level_list);
    my_free(sl);
}

void test_skip_list()
{
    skip_list* sl = new_skip_list();

    int count = 30;

    for (int i = 0; i <= count; i++)
        check2(sl->insert(sl, (void*)i, (void*)(i * 2)) == true);

    for (int i = 0; i <= count; i++)
        check2(sl->insert(sl, (void*)i, (void*)i) == false);

    for (list_node* level = sl->level_list->head; level != NULL; level = level->next)
    {
        list_ext* l = level->value;
        check2(l->head(l)->next != NULL);
    }

	int value = 0;
	check2(sl->find(sl, (void*)(count + 1), (void**)&value) == false);
	check2(sl->find(sl, (void*)(count + 2), (void**)&value) == false);

	for (int i = 0; i <= count; i++)
	{
		check2(sl->find(sl, (void*)i, (void**)&value) == true);
		check2(value == i * 2);
	}

	for (int i = 0; i <= count; i++)
	{
		check2(sl->delete(sl, (void*)i) == true);
	}

	for (int i = 100; i < 200; i++)
		check2(sl->insert(sl, (void*)i, (void*)(i)) == true);

	for (int i = 100; i < 200; i++)
		check2(sl->delete(sl, (void*)i) == true);

	for (int i = 200; i < 300; i++)
		check2(sl->delete(sl, (void*)i) == false);

	for (int i = 100; i < 200; i++)
		check2(sl->insert(sl, (void*)i, (void*)(i)) == true);

	for (int i = 100; i < 150; i++)
		check2(sl->delete(sl, (void*)i) == true);

    delete_skip_list(sl);
}

