#include "common.h"

extern void test_vector();
extern void test_p_6_5_boyer_moore();
extern void dump_leak();

int main()
{
    //test_vector();
    test_p_6_5_boyer_moore();

#ifdef _DEBUG
    dump_leak();
#endif
    system("pause");
}