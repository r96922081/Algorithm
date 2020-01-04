#pragma once
#pragma warning(disable : 4996)

#define _CRTDBG_MAP_ALLOC
#include "stdlib.h"
#include "crtdbg.h"

#include "assert.h"
#include "stdlib.h"
#include "string.h"
#include "memory.h"

typedef int bool;
#define true 1
#define false 0
#define max_len 255

void check(bool b);

typedef struct stack {
	int sp;
	void* array[max_len];
	void (*push)(struct stack* s, void* element);
	void* (*pop)(struct stack* s);
	void* (*top)(struct stack* s);
	bool (*empty)(struct stack* s);
	void (*clear)(struct stack* s);
}stack;

stack new_stack();