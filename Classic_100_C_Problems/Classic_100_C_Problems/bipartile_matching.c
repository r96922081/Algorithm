#include "common.h"

typedef struct edge {
    int src;
    int dest;
    int length;
}edge;

edge* new_edge(int src, int dest, int length)
{
    edge* e = (edge*)my_malloc(sizeof(edge));
    e->src = src;
    e->dest = dest;
    e->length = length;

    return e;
}

void init(vector* group1, vector* group2, vector* edges, bool** g1_used, bool** g2_used, list*** adj_lists, list*** selected)
{
    int node_count = group1->size + group2->size;
    *adj_lists = my_malloc(sizeof(list*) * node_count);
    *g1_used = my_malloc(sizeof(bool) * node_count);
    *g2_used = my_malloc(sizeof(bool) * node_count);
    *selected = my_malloc(sizeof(list*) * node_count);

    for (int i = 0; i < node_count; i++)
    {
        (*adj_lists)[i] = new_list();
        (*g1_used)[i] = false;
        (*g2_used)[i] = false;
        (*selected)[i] = new_list();
    }

    for (int i = 0; i < edges->size; i++)
    {
        edge* e = edges->at(edges, i);
        list* l = (*adj_lists)[e->src];
        l->append(l, (void*)e->dest);
        l = (*adj_lists)[e->dest];
        l->append(l, (void*)e->src);
    }
}

void get_unused_node(int* n1, int* n2, vector* group1, vector* group2, bool* g1_used, bool* g2_used)
{
    *n1 = -1;
    *n2 = -1;

    // find un-used node in g1
    int unused_g1 = -1;
    for (int i = 0; i < group1->size; i++)
    {
        int node = (int)group1->at(group1, i);
        if (g1_used[node] == false)
        {
            unused_g1 = node;
            break;
        }
    }

    if (unused_g1 == -1)
        return;

    // find un-used node in g2
    int unused_g2 = -1;
    for (int i = 0; i < group2->size; i++)
    {
        int node = (int)group2->at(group2, i);
        if (g2_used[node] == false)
        {
            unused_g2 = node;
            break;
        }
    }

    if (unused_g2 == -1)
        return;

    *n1 = unused_g1;
    *n2 = unused_g2;
}

bool dfs(stack_int* path, int current, int dest, list** adj_lists, bool* visited)
{
    if (visited[current])
        return false;
    visited[current] = true;

    path->push(path, current);
    if (current == dest)
        return true;

    list* l = adj_lists[current];

    for (list_node* list_node = l->head; list_node != NULL; list_node = list_node->next)
    {
        int next_node = (int)list_node->value;
        if (dfs(path, next_node, dest, adj_lists, visited))
            return true;
    }

    visited[current] = false;
    path->pop(path);
    return false;
}

void remove_selected_node(stack_int* path, list** selected, int node_count)
{
    bool* removed = (bool*)my_malloc(sizeof(bool) * node_count);
    for (int i = 0; i < node_count; i++)
        removed[i] = false;

    for (list_node* n = path->_s->list->head; n != NULL; n = n->next)
    {
        int current = (int)n->value;
        removed[current] = true;
        list* l = selected[current];

        for (list_node* n2 = l->head; n2 != NULL; n2 = n2->next)
            removed[(int)n2->value] = true;
    }

    for (int i = 0; i < node_count; i++)
    {
        if (removed[i])
            selected[i]->clear(selected[i]);
    }

    my_free(removed);
}

int bipartile_matching(vector* group1, vector* group2, vector* edges)
{
    bool* g1_used;
    bool* g2_used;
    list** adj_lists = NULL;
    list** selected = NULL;

    init(group1, group2, edges, &g1_used, &g2_used, &adj_lists, &selected);
    int node_count = group1->size + group2->size;

    bool end = false;

    while (!end)
    {
        bool* visited = my_malloc(sizeof(bool) * node_count);
        stack_int* path = new_stack_int();

        do
        {
            int n1 = -1;
            int n2 = -1;
            get_unused_node(&n1, &n2, group1, group2, g1_used, g2_used);

            if (n1 == -1 || n2 == -1)
            {
                end = true;
                break;
            }

            for (int i = 0; i < node_count; i++)
                visited[i] = false;

            bool ret = dfs(path, n1, n2, adj_lists, visited);
            
            if (ret == false)
            {
                end = true;
                break;
            }

            bool even = true;
            path->print(path);
            remove_selected_node(path, selected, node_count);

            int prev = -1;

            while (!path->empty(path))
            {
                int current = (int)path->pop(path);
                g1_used[current] = true;
                g2_used[current] = true;

                if (prev != -1)
                {
                    list* l1 = selected[prev];
                    l1->append(l1, (void*)current);

                    list* l2 = selected[current];
                    l2->append(l2, (void*)prev);
                }

                prev = current;
            }
        } while (false);

        my_free(visited);
        delete_stack_int(path);
    }

    int edge_count = 0;

    for (int i = 0; i < node_count; i++)
    {
        int current = i;
        list* l = selected[current];

        for (list_node* n = l->head; n != NULL; n = n->next)
        {
            if ((int)(n->value) > current)
            {
                printf("edge: %d - %d\n", current, (int)(n->value));
                fflush(stdout);
                edge_count++;
            }
        }
    }

    return edge_count;
}

void test1()
{
    vector* group1 = NULL;
    vector* group2 = NULL;
    vector* edges = NULL;

    group1 = new_vector();
    group1->append(group1, (void*)0);

    group2 = new_vector();
    group2->append(group2, (void*)1);

    edges = new_vector();
    edges->append(edges, (void*)new_edge(0, 1, 1));

    check2(bipartile_matching(group1, group2, edges) == 1);
    delete_vector(group1);
    delete_vector(group2);
    delete_vector_and_pointer(edges);
}

void test2()
{
    vector* group1 = NULL;
    vector* group2 = NULL;
    vector* edges = NULL;

    group1 = new_vector();
    group1->append(group1, (void*)0);
    group1->append(group1, (void*)1);
    group1->append(group1, (void*)2);
    group1->append(group1, (void*)6);
    group1->append(group1, (void*)8);

    group2 = new_vector();
    group2->append(group2, (void*)3);
    group2->append(group2, (void*)4);
    group2->append(group2, (void*)5);
    group2->append(group2, (void*)7);

    edges = new_vector();
    edges->append(edges, (void*)new_edge(0, 3, 1));
    edges->append(edges, (void*)new_edge(1, 3, 1));
    edges->append(edges, (void*)new_edge(1, 5, 1));
    edges->append(edges, (void*)new_edge(2, 3, 1));
    edges->append(edges, (void*)new_edge(2, 4, 1));
    edges->append(edges, (void*)new_edge(6, 7, 1));

    check2(bipartile_matching(group1, group2, edges) == 4);
    delete_vector(group1);
    delete_vector(group2);
    delete_vector_and_pointer(edges);
}

void test3()
{
    vector* group1 = NULL;
    vector* group2 = NULL;
    vector* edges = NULL;

    group1 = new_vector();
    for (int i = 0; i <= 5; i++)
        group1->append(group1, (void*)i);

    group2 = new_vector();
    for (int i = 6; i <= 11; i++)
        group2->append(group2, (void*)i);

    edges = new_vector();
    edges->append(edges, (void*)new_edge(0, 6, 1));
    edges->append(edges, (void*)new_edge(1, 6, 1));
    edges->append(edges, (void*)new_edge(1, 7, 1));
    edges->append(edges, (void*)new_edge(2, 6, 1));
    edges->append(edges, (void*)new_edge(2, 8, 1));
    edges->append(edges, (void*)new_edge(2, 9, 1));
    edges->append(edges, (void*)new_edge(3, 9, 1));
    edges->append(edges, (void*)new_edge(3, 10, 1));
    edges->append(edges, (void*)new_edge(4, 10, 1));
    edges->append(edges, (void*)new_edge(5, 10, 1));
    edges->append(edges, (void*)new_edge(5, 11, 1));

    check2(bipartile_matching(group1, group2, edges) == 6);
    delete_vector(group1);
    delete_vector(group2);
    delete_vector_and_pointer(edges);
}

void test_bipartile_matching()
{
    test1();
    test2();
    test3();
}