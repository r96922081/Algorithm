#pragma once

struct list_node;

typedef struct list {
    struct list_node* (*append)(struct list*, void*);
    struct list_node* (*insert_after)(struct list*, struct list_node*, void*);
    struct list_node* (*insert_before)(struct list*, struct list_node*, void*);
    void (*insert_after_2)(struct list*, struct list_node*, struct list_node*);
    void (*insert_before_2)(struct list*, struct list_node*, struct list_node*);
    void(*remove)(struct list*, struct list_node*);
    void(*clear)(struct list*);
    void(*clear_and_free_pointer)(struct list*);
    void(*print)(struct list*);
    struct list_node* head;
    struct list_node* tail;
}list;

typedef struct list_node {
    struct list_node* next;
    struct list_node* prev;
    void* value;
}list_node;

list* new_list();
void delete_list(list* l);
void delete_list_and_pointer(list* l);
