#include "my_c_lib.h"
#include "vector.h"

void vector_append(vector* v, void* value)
{
    if (v->_capacity == 0)
    {
        v->_capacity = 1;
        v->_content = (void**)my_malloc(sizeof(void*));
    }
    if (v->size + 1 > v->_capacity)
    {
        void** old_content = v->_content;
        v->_content = my_malloc(sizeof(void*) * v->_capacity * 2);
        memset(v->_content, 0, sizeof(void*) * v->_capacity * 2);

        for (int i = 0; i < v->_capacity; i++)
            v->_content[i] = old_content[i];

        my_free(old_content);
        v->_capacity *= 2;
    }

    v->_content[v->size++] = (void*)value;
}

void vector_remove2(vector* v, int index)
{
    if (index >= v->size || index < 0)
        raise();

    if (index == v->size - 1)
    {
        v->size--;
    }
    else
    {
        void** old_content = v->_content;
        v->_content = my_malloc(sizeof(void*) * v->_capacity);
        memset(v->_content, 0, sizeof(void*) * v->_capacity);

        int j = 0;
        for (; j < index; j++)
            v->_content[j] = old_content[j];

        j++;

        for (;j < v->size; j++)
            v->_content[j - 1] = old_content[j];

        my_free(old_content);
        v->size--;
    }
}

void* vector_at(struct vector* v, int index)
{
    if (index >= v->size || index < 0)
        raise();

    return v->_content[index];
}

vector* new_vector()
{
    vector* v = my_malloc(sizeof(vector));
    v->_capacity = 0;
    v->size = 0;
    v->append = vector_append;
    v->at = vector_at;
    v->remove = vector_remove2;
    v->_content = NULL;

    return v;
}

void delete_vector(vector* v)
{
    if (v->_content != NULL)
        my_free(v->_content);
    my_free(v);
}

void delete_vector_and_pointer(vector* v)
{
    for (int i = 0; i < v->size; i++)
        my_free(v->at(v, i));

    delete_vector(v);
}

void test_vector()
{
    vector* v = new_vector();
    for (int i = 0; i < 17; i++)
        v->append(v, (void*)i);
    check2(v->size == 17);
    
    for (int i = 0; i < 17; i++)
        check2(v->at(v, i) == (void*)i);

    v->remove(v, 0);
    check2(v->at(v, 0) == (void*)1);

    v->remove(v, 2);
    check2(v->at(v, 2) == (void*)4);

    for (int i = 0; i < 15; i++)
        v->remove(v, 0);

    check2(v->size == 0);

    delete_vector(v);
}