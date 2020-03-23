#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "vector.h"

void check2(int v);
void* my_malloc_imp(size_t size, char* file_name, int line_number);
void my_free_imp(void* address);
void raise();

#ifdef _DEBUG
#define my_malloc(size) my_malloc_imp(size, __FILE__, __LINE__)
#define my_free my_free_imp
#else
#define my_malloc malloc
#define my_free free
#endif