#include "common.h"

extern void test_vector();
extern void test_list();
extern void test_stack();
extern void test_p_6_5_boyer_moore();
extern void test_p_6_1_parenthses_matching();
extern void dump_leak();

int main()
{
    //test_list();
    //test_vector();
    //test_stack();
    //test_p_6_5_boyer_moore();
    test_p_6_1_parenthses_matching();

#ifdef _DEBUG
    dump_leak();
#endif
    system("pause");
}