import unittest
from collections import deque

class binary_tree_node:   
    null = None
    def __init__(self):
        self.parent = self.get_null()
        self.left = self.get_null()
        self.right = self.get_null()
        
    def get_null(self):
        return binary_tree_node.null
        
    def set_null(self, null):
        binary_tree_node.null = null
        
    def setleft(self, bt_node):
        self.left = bt_node
        bt_node.parent = self
        
    def setright(self, bt_node):
        self.right = bt_node
        bt_node.parent = self  
  
    def getleft(self):
        return self.left
        
    def getright(self):
        return self.right
        
    def get_indention_and_maxkeylen(self, node, indention_count, maxlen):
        ''' For initial call, pass indention_count = 0, maxlen = 0'''
        if node.getleft() != self.get_null():
            indention_count, maxlen = self.get_indention_and_maxkeylen(node.getleft(), indention_count, maxlen)
            
        node.indention = indention_count
        indention_count += 1
        maxlen = max(maxlen, len(str(node)))
        
        if node.right != self.get_null():
            indention_count, maxlen = self.get_indention_and_maxkeylen(node.right, indention_count, maxlen)
            
        return indention_count, maxlen
        
    def print_tree(self):
        indention_count, maxlen = self.get_indention_and_maxkeylen(self, 0, 0)

        q = deque([])
        
        class plainobject:
            pass
            
        q_element = plainobject()
        q_element.node = self
        q_element.level = 1
        q.append(q_element)
        
        printed_indention_count = 0        
        while len(q) != 0:
            q_element = q.popleft()
            node = q_element.node
            level = q_element.level

            last_in_this_level = False
            if len(q) == 0 or level != q[0].level:
                last_in_this_level = True

            for i in range(node.indention  - printed_indention_count) :
                for i in range(maxlen):
                    print(' ',  end = '')
                printed_indention_count += 1
            
            for i in range(maxlen - len(str(node))):
                print(' ',  end = '')
            print(node,  end = '')
            printed_indention_count += 1
            
            if last_in_this_level:
                print('')
                printed_indention_count = 0
            
            if node.getleft() != self.get_null():
                q_element = plainobject()
                q_element.node = node.getleft()
                q_element.level =  level + 1
                q.append(q_element)
            if node.right != self.get_null():
                q_element = plainobject()
                q_element.node = node.right
                q_element.level =  level + 1
                q.append(q_element)


class mynode(binary_tree_node):
    def __init__(self, key):
        super().__init__()
        self.key = key
        
    def __str__(self):
        return str(self.key)
        
    def getkey(self):
        return self.key
        
    def setkey(self, key):
        self.key = key

class TestMe(unittest.TestCase):
    def test1(self):
        node1 = mynode(1)
        node2 = mynode(22)
        node3 = mynode(33)
        node4 = mynode(4)   
        node5 = mynode(5)  
        node6 = mynode(6)          
        node1.setleft(node2)
        node1.setright(node3)
        node2.setright(node4)
        node3.setright(node5)
        node5.setleft(node6)
        
        print('')
        node1.print_tree()
        pass
        
    
if __name__ == '__main__':
    unittest.main()
