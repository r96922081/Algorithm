#pragma once

typedef struct vector
{
    void(*append)(struct vector*, void*);
    int(*size)(struct vector*);
    void*(*value)(struct vector*, int index);
    void(*remove)(struct vector*, int index);

    int size_;
    int capacity_;
    void** content_;
}vector;

vector* new_vector();
void delete_vector(vector* v);
void delete_vector_and_pointer(vector* v);