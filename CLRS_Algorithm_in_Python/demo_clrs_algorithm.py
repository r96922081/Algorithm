import unittest
import random
import sys

sys.path.append('CLRS_algorithm')

from b_trees import btree
from binary_search_tree import binary_search_tree
from disjoint_set import find_set, union, disjoint_set_node
from graph_algorithm import find_scc, has_cycle
from matrix_operation import solve_matrix
from utility import matrix,create_random_graph
from heap import priority_queue, heaptype
from fib_heap import fib_heap, fib_heap_node
from mst import kruskal_for_undirected_graph, prims_for_undirected_graph
from red_black_tree import red_black_tree, red_black_tree_node
from veb_tree import veb_node
from single_source_shortest_path import bellman_ford, shortest_path_for_directed_acyclic_graph, dijkstra_for_nonnegative_wieght
from hash import get_perfect_hash, get_2_level_perfect_hash, select_distinct_keys

class demo_clrs_algorithm_test(unittest.TestCase):
    def tearDown(self):
        print('\n=================')
        
    def test_btree(self):
        print('B-Tree demo')
        t = 5
        print('Create B-Tree with t = ' + str(t))
        btree1 = btree(t)
        print('insert even number in 0 ~ 999')
        for i in range(1000):
            if i % 2 == 0:
                btree1.insert(i)
        
        key = 998
        node = btree1.search(key)
        print('Search key ' + str(key) + ' result = ' + str(node))
                
        key = 499
        node = btree1.search(key)
        print('Search key ' + str(key) + ' result = ' + str(node))    
     
    def test_binary_search_tree(self):
        print('Binary Search Tree demo')
        bst1 = binary_search_tree()
        print('Insert key % 2 == 0')        
        for i in range(1000):
            if i % 2 == 0:
                bst1.insert(i)
        print('delete key % 4 == 0')        
        for i in range(1000):
            if i % 4 == 0:
                bst1.delete(i)      
                
        for key in [1, 20, 22]:
            print('Search key ' + str(key) + ' result = ',  bst1.search(key))

    def test_red_black_tree(self):
        print('Red Black Tree demo')
        rb_tree = red_black_tree()
        print('Insert key % 2 == 0')        
        for i in range(1000):
            if i % 2 == 0:
                rb_tree.insert(red_black_tree_node(rb_tree, i))
        print('delete key % 4 == 0')        
        for i in range(1000):
            if i % 4 == 0:
                n = rb_tree.search(i)
                rb_tree.delete(n)     
                
        for key in [1, 20, 22]:
            print('Search key ' + str(key) + ' result = ',  rb_tree.search(key))   

    def test_vEB_tree(self):
        print('van Emde Boas demo')
        # u must be power of 2
        u = 2 ** 10 
        n = veb_node(u, None, None)
        print('Insert key % 2 == 0')        
        for i in range(u):
            if i % 2 == 0:
                n.insert(i)
        print('delete key % 4 == 0')        
        for i in range(u):
            if i % 4 == 0:
                n.delete(i)   
                
        for key in [1, 20, 22]:
            print('Search key ' + str(key) + ' result = ',  n.member(key))       
            
    def test_disjoint_set(self):
        print('Disjoint set demo')  
        print('Insert key 1 ~ 4, union 1,2; union 1,3')
        n1 = disjoint_set_node(1)
        n2 = disjoint_set_node(2)
        n3 = disjoint_set_node(3)
        n4 = disjoint_set_node(4)     
        
        union(find_set(n1), find_set(n2))
        union(find_set(n1), find_set(n3))
        
        print('1 in {' + str(find_set(n1).key) + '}')
        print('2 in {' + str(find_set(n2).key) + '}')
        print('3 in {' + str(find_set(n3).key) + '}')
        print('4 in {' + str(find_set(n4).key) + '}')
        
    def test_find_scc(self):
        print('Find strongly connected component Demo')  
        G = matrix(4, 4)
        G[0][1] = 1
        G[1][2] = 1
        G[2][0] = 1
        G[0][3] = 1
        print('adjaceny matrx is')
        print(G)

        print('strongly connected component is')
        all_scc = find_scc(G)
        print(all_scc)
        
    def test_matrix(self):
        print('Matrix demo')  
        print('Solve Ax = b')
        print('A = ')
        A = matrix(3, 3)
        A[0] = [1, 1, 4]
        A[1] = [2, 1, 2]
        A[2] = [1, 3, 1]
        print(A)
            
        print('b = ')
        b = matrix(3, 1)
        b[0][0] = 15
        b[1][0] = 10
        b[2][0] = 10
        print(b)
        
        print('x = ')
        print(solve_matrix(A, b))
        
    def test_priority_queue(self):
        print('priority queue (using heap) demo')          
                
        nodes = []
        for _ in range(10):
            nodes.append(random.randint(1, 100))
        print('insert those node to priority queue: ',  end = '')
        for node in nodes:
            print(node,  end = ' ')
        print('')
        
        q = priority_queue(heaptype.max, sys.maxsize, -sys.maxsize + 1)
        for node in nodes:
            q.insert(node, node)
            
        print('extract sequentially: ',  end = '')
        while q.heapsize > 0:
            node = q.extract()
            print(node,  end = ' ')
        print('')
        
    def test_fib_heap(self):
        print('fib heap demo')
      
        nodes = []
        for _ in range(10):
            nodes.append(fib_heap_node(random.randint(1, 100)))
        print('insert those node to fib heap: ',  end = '')
        for node in nodes:
            print(node,  end = ' ')
        print('')
        
        h = fib_heap()
        for node in nodes:
            h.insert(node)
            
        print('extract sequentially: ',  end = '')
        while h.n > 0:
            node = h.extract_min()
            print(node,  end = ' ')
        print('')

    def test_mst(self):
        print('minimum spanning tree demo')
      
        node_count = 6
        while True:
            V, E = create_random_graph(node_count, node_count ** 2, False)
            all_sccs = find_scc(E)
            if len(all_sccs) == 1:
                break

        print('adjance-matrix = \n' + str(E))
        A1 = kruskal_for_undirected_graph(V, E)

        print('MST edges by Kruskal= ')
        for e in A1:
            print(e)

        A2 = prims_for_undirected_graph(V, E, 0)
        print('MST edges by Prim''s= ')
        for e in A2:
            print(e)
            
    def test_single_source_shortest_path(self):
        print('single source shortest path demo')
        E = matrix(3, 3)
        E[0][1] = -1
        E[1][0] = -1
        print('use bellman ford to detect negative cycle:')
        print('adjancy matrix is:')
        print(E)
        print('has negative cycle by bellman ford: ',  end = '')
        no_negative_cycle,  answer = bellman_ford(E, 0)
        print(not no_negative_cycle)
        
        cycle = True 
        while cycle:
            V, E = create_random_graph(4, 16, True)        
            cycle = has_cycle(E)

        print('test on this no cycled adjancey matrix:')
        print(E)
        no_negative_cycle,  answer = bellman_ford(E, 0)
        print('answer by bellman_ford: ')
        for i in range(len(answer)):
            print('shortest path from 0 to ' + str(i) + ' is ' + str(answer[i].d) + ' ')
            
        answer = shortest_path_for_directed_acyclic_graph(E, 0)
        print('answer by shortest_path_algorithm_for_DAG: ')
        for i in range(len(answer)):
            print('shortest path from 0 to ' + str(i) + ' is ' + str(answer[i].d) + ' ')
            
            
        answer = dijkstra_for_nonnegative_wieght(E, 0)
        print('answer by dijkstra_for_nonnegative_wieght: ')
        for i in range(len(answer)):
            print('shortest path from 0 to ' + str(i) + ' is ' + str(answer[i].d) + ' ')
            
    def test_hash_function(self):
        print('perfect hash demo')
        
        keys = select_distinct_keys(99, 9)            
        print('keys = ' + str(keys) + '\n')
        
        print('1 level perfect hash')
        perfect_hash = get_perfect_hash(keys)
        hash_values = []
        for key in keys:
            hash_values.append(perfect_hash(key))
        print('hash values = ' + str(hash_values))
        print('table size = ' + str(perfect_hash.m))
        print('perfect hash function = ' + str(perfect_hash))
        print('')
        
        print('2 level perfect hash')
        level_1_table_size = 3
        level_1_hash,  level_2_hashes = get_2_level_perfect_hash(level_1_table_size, keys)
        hash_values_2d = []
        keys_2d = []
        for i in range(level_1_table_size):
            hash_values_2d.append([])
            keys_2d.append([])
            
        for key in keys:
            level_1_index = level_1_hash(key)
            level_2_hash = level_2_hashes[level_1_index]
            keys_2d[level_1_index].append(key)
            hash_values_2d[level_1_index].append(level_2_hash(key))
            
        for i in range(len(level_2_hashes)):
            print('keys = ',  end = '')
            print(keys_2d[i],  end = ', ')
            print('hash values = ',  end = '')
            hash_values = hash_values_2d[i]
            print(hash_values,  end = ', ')
            
            hash_function = level_2_hashes[i]
            if hash_function != None:
                print('table size = ' + str(hash_function.m),  end = ', ')
                print('hash function = ' + str(hash_function),  end = '')
            print('')

if __name__ == '__main__':
    unittest.main()
