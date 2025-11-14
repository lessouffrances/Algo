class TreeNode:
    """Node class for Binary Search Tree"""
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

class BinarySearchTree:
    def __init__(self):
        self.root = None

    def insert(self, val):
        self.root = self._insert_recursive(self.root, val)
    
    def _insert_recursive(self, node, val):
        if node is None:
            return TreeNode(val)
        
        if val < node.val:
            node.left = self._insert_recursive(node.left, val)

        elif val > node.val:
            node.right = self._insert_recursive(node.right, val)
    
    def search(self, target):
        return self._search_recursive(self.root, target)
    
    def _search_recursive(self, node, target):
        if node is None:
            return False
        
        if node.val == target:
            return True
        
        if target < node.val:
            return self._search_recursive(node.left, target)
        
        elif target > node.val:
            return self._search_recursive(node.right, target)
    
    

        


