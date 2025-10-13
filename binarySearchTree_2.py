class TreeNode:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
    
class BinaryTree:
    def __init__(self):
        self.root = None
    
    def search(self, target):
        return self._search_recursive(self.root, target)

    def _search_recursive(self, treeNode, target):
        if treeNode == None:
            return False
        if treeNode.data > target:
            return self._search_recursive(treeNode.left, target)
        elif treeNode.data < target:
            return self._search_recursive(treeNode.right, target)
        else:
            return True

    def insert(self, data):
       self.root = self._insert_recursive(self.root, data)
    
    def _insert_recursive(self, treeNode, data):
        if treeNode == None:
            return TreeNode(data)
        
        if treeNode.data > data:
            treeNode.left = self._insert_recursive(treeNode.left, data)

        elif treeNode.data < data:
            treeNode.right = self._insert_recursive(treeNode.right, data)
        
        return treeNode

def main():
    tree = BinaryTree()
    tree.insert(2)
    tree.insert(5)
    print(tree.search(5))
main()
        

