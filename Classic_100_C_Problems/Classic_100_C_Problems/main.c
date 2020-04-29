#include "common.h"

extern void test_vector();
extern void test_list();
extern void test_stack();
extern void test_queue();
extern void test_skip_list();

extern void test_p_6_5_boyer_moore();
extern void test_p_6_1_parenthses_matching();

extern void test_bipartile_matching();

extern void dump_leak();

void test_data_structure()
{
    test_list();
    test_vector();
    test_stack();
    test_queue();
    test_skip_list();
}

void test_algorithm()
{
    //test_p_6_5_boyer_moore();
    //test_p_6_1_parenthses_matching();
    test_bipartile_matching();
}

int main()
{
    test_data_structure();
    //test_algorithm();

#ifdef _DEBUG
    dump_leak();
#endif
    system("pause");
}