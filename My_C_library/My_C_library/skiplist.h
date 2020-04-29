#pragma once
#include "list.h"
#include "my_c_lib.h"


struct list_ext;

/*
level_list_tail->  h     2
                   h     2  3
level_list_head->  h  1  2  3  4  5


list_ext->  h     2
list_ext->  h     2  3
list_ext->  h  1  2  3  4  5
            ^
            |
           list
*/
typedef struct skip_list {
    struct list* level_list;
    enum bool (*insert)(struct skip_list*, void* key, void* value);
	enum bool (*find)(struct skip_list*, void* key, void** value);
	enum bool(*delete)(struct skip_list*, void* key);
    void(*print)(struct skip_list*);
}skip_list;

skip_list* new_skip_list();
void delete_skip_list(skip_list*);