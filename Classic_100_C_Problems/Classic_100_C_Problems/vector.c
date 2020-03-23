#include "common.h"
#include "vector.h"

void append(vector* v, void* value)
{
    if (v->capacity_ == 0)
    {
        v->capacity_ = 1;
        v->content_ = (void**)my_malloc(sizeof(void*));
    }
    if (v->size_ + 1 > v->capacity_)
    {
        void** old_content = v->content_;
        v->content_ = my_malloc(sizeof(void*) * v->capacity_ * 2);
        memset(v->content_, 0, sizeof(void*) * v->capacity_ * 2);

        for (int i = 0; i < v->capacity_; i++)
            v->content_[i] = old_content[i];

        my_free(old_content);
        v->capacity_ *= 2;
    }

    v->content_[v->size_++] = (void*)value;
}

void remove2(vector* v, int index)
{
    if (index >= v->size_ || index < 0)
        raise();

    if (index == v->size_ - 1)
    {
        v->size_--;
    }
    else
    {
        void** old_content = v->content_;
        v->content_ = my_malloc(sizeof(void*) * v->capacity_);
        memset(v->content_, 0, sizeof(void*) * v->capacity_);

        int j = 0;
        for (; j < index; j++)
            v->content_[j] = old_content[j];

        j++;

        for (;j < v->size_; j++)
            v->content_[j - 1] = old_content[j];

        my_free(old_content);
        v->size_--;
    }
}

int size(vector* v)
{
    return v->size_;
}

void* value(struct vector* v, int index)
{
    if (index >= v->size_ || index < 0)
        raise();

    return v->content_[index];
}

vector* new_vector()
{
    vector* v = my_malloc(sizeof(vector));
    v->capacity_ = 0;
    v->size_ = 0;
    v->append = append;
    v->value = value;
    v->size = size;
    v->remove = remove2;
    v->content_ = NULL;

    return v;
}

void delete_vector(vector* v)
{
    if (v->content_ != NULL)
        my_free(v->content_);
    my_free(v);
}

void delete_vector_and_pointer(vector* v)
{
    for (int i = 0; i < v->size(v); i++)
        my_free(v->value(v, i));

    delete_vector(v);
}

void test_vector()
{
    vector* v = new_vector();
    for (int i = 0; i < 17; i++)
        v->append(v, (void*)i);
    check2(v->size(v) == 17);
    
    for (int i = 0; i < 17; i++)
        check2(v->value(v, i) == (void*)i);

    v->remove(v, 0);
    check2(v->value(v, 0) == (void*)1);

    v->remove(v, 2);
    check2(v->value(v, 2) == (void*)4);

    for (int i = 0; i < 15; i++)
        v->remove(v, 0);

    check2(v->size(v) == 0);

    delete_vector(v);
}