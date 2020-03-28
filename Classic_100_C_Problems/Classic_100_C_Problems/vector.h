#pragma once

typedef struct vector
{
    void(*append)(struct vector*, void*);
    void*(*value)(struct vector*, int index);
    void(*remove)(struct vector*, int index);

    int size;
    int _capacity;
    void** _content;
}vector;

vector* new_vector();
void delete_vector(vector* v);
void delete_vector_and_pointer(vector* v);