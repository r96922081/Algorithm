#include "util.h"

void alg_6_1(char* input, char* output)
{
	stack sp = new_stack();
	stack* s = &sp;

	for (size_t i = 0; i < strlen(input); i++)
		output[i] = ' ';
	output[strlen(input)] = '\0';

	for (size_t i = 0; i < strlen(input); i++)
	{
		char c = input[i];
		if (c == ')')
		{
			if (s->empty(s))
				output[i] = '$';
			else
			{
				free(s->pop(s));
			}
			
		}
		else if (c == '(')
		{
			int* a = malloc(sizeof(int));
			*a = i;
			s->push(s, a);
		}
	}

	while (!(s->empty(s)))
	{
		int* a = s->pop(s);
		output[*a] = '$';
		free(a);
	}
}


void run_6_1()
{
	char input[255];
	char output[255];

	strcpy(input, "((abc)");
	alg_6_1(input, output);
	check(strcmp(output, "$     ") == 0);

	strcpy(input, "(abc)");
	alg_6_1(input, output);
	check(strcmp(output, "     ") == 0);

	strcpy(input, "(abc))  (");
	alg_6_1(input, output);
	check(strcmp(output, "     $  $") == 0);

	strcpy(input, "())  (())) ");
	alg_6_1(input, output);
	check(strcmp(output, "  $      $ ") == 0);

	strcpy(input, "");
	alg_6_1(input, output);
	check(strcmp(output, "") == 0);
}