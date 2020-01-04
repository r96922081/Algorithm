#include "util.h"

void check(bool b)
{
	if (b == false)
	{
		assert(false);
	}
}

void stack_push(struct stack* s, void* element)
{
	assert(s->sp < max_len);
	s->array[s->sp] = element;
	s->sp++;
}

void* stack_pop(struct stack* s)
{
	assert(s->sp > 0);
	s->sp--;

	return s->array[s->sp];
}

void* stack_top(struct stack* s)
{
	assert(0 < s->sp && s->sp <= max_len);
	return s->array[s->sp - 1];
}

bool stack_empty(struct stack* s)
{
	return s->sp == 0;
}

void stack_clear(struct stack* s)
{
	for (int i = 0; i < s->sp; i++)
		free(s->array[i]);

	s->top = 0;
}

stack new_stack()
{
	stack s;
	s.sp = 0;
	s.push = stack_push;
	s.pop = stack_pop;
	s.top = stack_top;
	s.empty = stack_empty;
	s.clear = stack_clear;

	return s;
}