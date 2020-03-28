#include "common.h"
#include "vector.h"
#include "list.h"

static void check(int b)
{
    if (!b)
    {
        int* n = 0;
        *n = 0;
    }
}

int p_6_5_boyer_moore(char* s, char* key);

int naive_string_match(char* s, char* key)
{
    for (int i = 0; i < (int)strlen(s); i++)
    {
        if (strncmp(s + i, key, strlen(key)) == 0)
            return i;
    }

    return -1;
}

#define digit_count (3)

void test_p_6_5_boyer_moore3(char* s, char* key, int current_digit_count)
{
    if (current_digit_count == digit_count)
        return;

    for (int i = 0; i < digit_count; i++)
    {
        key[digit_count - 1 - current_digit_count] = '0' + i;

        char* key2 = key + digit_count - 1 - current_digit_count;

        printf("s = %s, key = %s\n", s, key2);
        int answer1 = naive_string_match(s, key2);
        int answer2 = p_6_5_boyer_moore(s, key2);
        check(answer1 == answer2);

        test_p_6_5_boyer_moore3(s, key, current_digit_count + 1);
    }
}

void test_p_6_5_boyer_moore2(char* s, int i)
{
    if (i == digit_count)
    {
        char key[digit_count + 1];
        key[digit_count] = '\0';

        test_p_6_5_boyer_moore3(s, key, 0);
        return;
    }

    for (int m = 0; m < digit_count; m++)
    {
        s[i] = '0' + m;
        test_p_6_5_boyer_moore2(s, i + 1);
    }
}

void test_p_6_5_boyer_moore()
{
    check(naive_string_match("bc", "a") == -1);
    check(naive_string_match("bca", "a") == 2);

    char s[digit_count + 1];
    s[digit_count] = '\0';
    for (int i = 0; i < digit_count; i++)
        s[i] = '0';

    test_p_6_5_boyer_moore2(s, 0);
}

int p_6_5_boyer_moore(char* s, char* key)
{
    list* index[digit_count];
    for (int i = 0; i < digit_count; i++)
    {
        index[i] = new_list();
    }

    int key_len = strlen(key);

    for (int i = 0; i < key_len; i++)
    {
        char s2 = key[key_len - 1 - i];
        list* l = index[s2 - '0'];
        l->append(l, (void*)(key_len - 1 - i));
    }

    int answer = -1;
    int s_index = key_len - 1;
    list* l = index[s[s_index] - '0'];

    while (s_index < (int)strlen(s))
    {
        for (list_node* n = l->head; n != NULL; n = n->next)
        {
            char* s2 = s + s_index - (int)n->value;
            if (strncmp(s2, key, strlen(key)) == 0)
            {
                answer = s_index - (int)n->value;
                break;
            }
        }

        if (answer != -1)
            break;

        s_index += key_len;
        l = index[s[s_index] - '0'];
    }

    for (int i = 0; i < digit_count; i++)
    {
        delete_list(index[i]);
    }

    return answer;
}