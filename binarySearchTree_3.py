class Treenode:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

class BinarySearchTree:
    def __init__(self) -> None:
        self.root = None
    
    def search(self, target):
        return self._search_recursive(self.root, target)
    
    def _search_recursive(self, treenode, target):
        if treenode == None:
            return False
        
        if treenode.data > target:
            return self._search_recursive(treenode.left, target)
        
        elif treenode.data < target:
            return self._search_recursive(treenode.right, target)
        
        else:
            return True
    
    def insert(self, data):
        self.root = self._insert_recursive(self.root, data)
    
    def _insert_recursive(self, treenode, data):
        if treenode == None:
            return Treenode(data)
        
        if treenode.data > data:
            treenode.left = self._insert_recursive(treenode.left, data)

        elif treenode.data < data:
            treenode.right = self._insert_recursive(treenode.right, data)
        
        return treenode

def main():
    tree = BinarySearchTree()
    nums = [5, 1, 10, 6, 4, 2]

    for num in nums:
        tree.insert(num)

    for num in nums:
        print(tree.search(num)) 
    
    print(tree.search(100))
    
    
    


main()



