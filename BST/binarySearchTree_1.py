class TreeNode:
    def __init__(self, data) -> None:
        self.data = data
        self.left = None
        self.right = None

class BinarySearchTree:
    def __init__(self) -> None:
        self.root = None
    
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

def main():
    arr = [2, 4, 6, 8, 10, 12, 14, 16, 18]
    tree = BinarySearchTree()

    for i in range(len(arr)):
        tree.insert(arr[i])
    print(tree.search(10))
main()
            