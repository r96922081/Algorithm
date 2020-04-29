#include "my_c_lib.h"

void check2(int v)
{
    if (!v)
    {
        int* n = 0;
        *n = 0;
    }
}

void raise()
{
    int* n = 0;
    *n = 0;
}

typedef struct {
    void* address;
    int size;
    char file_name[256];
    int line_number;
    int index;
}memory_info;

int array_size = 0;
int current_index = -1;
memory_info* allocated = NULL;

void* my_malloc_imp(size_t size, char* file_name, int line_number)
{
    if (allocated == NULL)
    {
        array_size = 1;
        allocated = (memory_info*)malloc(sizeof(memory_info) * array_size);
    }
    else if (current_index + 1 == array_size)
    {
        memory_info* old_allocated = allocated;
        allocated = (memory_info*)malloc(sizeof(memory_info) * array_size * 2);
        for (int i = 0; i < array_size; i++)
            allocated[i] = old_allocated[i];

        array_size *= 2;
        free(old_allocated);
    }

    current_index++;
    void* ret = malloc(size);

    memory_info* mem = &allocated[current_index];
    mem->address = ret;
    mem->size = size;
    strcpy_s(mem->file_name, 255, file_name);
    mem->line_number = line_number;
    mem->index = current_index;

    if (mem->index == 6)
    {
        int a = 1;
        int b = 2;
        int  c = a / b;
    }

    return ret;
}

void my_free_imp(void* address)
{
    int found = 0;
    for (int i = 0; i <= current_index; i++)
    {
        if (allocated[i].address == address)
        {
            allocated[i].address = NULL;
            found = 1;
            break;
        }
    }

    if (!found)
        raise();

    free(address);
}

void dump_leak()
{
    for (int i = 0; i <= current_index; i++)
    {
        memory_info* mem = &allocated[i];
        if (mem->address != NULL)
        {
            printf("addr = %08X, size = %d, file = %s, line = %d, index = %d\n", (unsigned int)(mem->address), mem->size,
                mem->file_name, mem->line_number, mem->index);
        }
    }
}