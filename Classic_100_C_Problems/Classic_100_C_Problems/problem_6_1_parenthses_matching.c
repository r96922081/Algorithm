#include "common.h"

static void check(int b)
{
    if (!b)
    {
        int* n = 0;
        *n = 0;
    }
}


void parenthses_matching(char* input, char* output)
{
	stack* s = new_stack();

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
				s->pop(s);
			}
			
		}
		else if (c == '(')
		{
			s->push(s, (void*)i);
		}
	}

	while (!(s->empty(s)))
	{
		int a = (int)(s->pop(s));
		output[a] = '$';
	}

    delete_stack(s);
}


void test_p_6_1_parenthses_matching()
{
	char input[255];
	char output[255];

	strcpy_s(input, 255, "((abc)");
	parenthses_matching(input, output);
	check(strcmp(output, "$     ") == 0);

	strcpy_s(input, 255, "(abc)");
	parenthses_matching(input, output);
	check(strcmp(output, "     ") == 0);

	strcpy_s(input, 255, "(abc))  (");
	parenthses_matching(input, output);
	check(strcmp(output, "     $  $") == 0);

	strcpy_s(input, 255, "())  (())) ");
	parenthses_matching(input, output);
	check(strcmp(output, "  $      $ ") == 0);

	strcpy_s(input, 255, "");
	parenthses_matching(input, output);
	check(strcmp(output, "") == 0);
}