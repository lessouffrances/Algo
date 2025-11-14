// remember to clean the memory of the tree 
#include <iostream>
#include <cstdio>

using namespace std;

struct Node 
{
    int val;
    Node* left;
    Node* right;
    Node* parent;
    
    // Node constructor 
    Node(int x): val(x), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BST 
{
    private:
    Node* root;
    
    // private insert 
    Node* insertHelper(Node* node, int val, Node* parent=nullptr) 
    {
        if (!node) {
            Node* newNode = new Node(val);
            newNode->parent = parent;
            return newNode;
        }


        if (node->val > val) {
            node->left = insertHelper(node->left, val, node);
        } else if (node->val < val) {
            node->right = insertHelper(node->right, val, node);
        }
        return node;
    }

    // in-order traverse the BST
    void inOrderTraverseHelper(Node* node) 
    {
        if (!node) return;

        inOrderTraverseHelper(node->left);
        printf("%d ", node->val);
        inOrderTraverseHelper(node->right);
    }

    // left-most node of a subtree
    Node* subtreeFirstHelper(Node* node) 
    {
        if (!node) return nullptr;

        while(node->left) {
            node = node->left;
        }
        return node;
    }

    // right-most node of a subtree
    Node* subtreeLastHelper(Node* node) 
    {
        if (!node) return nullptr;

        while(node->right) {
            node = node->right;
        }
        return node;
    }

    // return the predecessor of some node
    Node* predecessorHelper(Node* node)
    {
        if (!node) return nullptr;

        if (node->left) {
            return subtreeLastHelper(node->left);
        }

        while (node->parent) {
            if (node == node->parent->right) {
                return node->parent;
            }
            node = node->parent;
        }

        return nullptr;
    }
    

    // return the successor of some node
    Node* successorHelper(Node* node) 
    {
        if (!node) return nullptr;

        if (node->right) {
            return subtreeFirstHelper(node->right);
        }
        
        while (node->parent) {
            if (node == node->parent->left) {
                return node->parent;
            }
            node = node->parent;
        }

        return nullptr;
    }

    // insert a node after some node 
    void subtreeInsertAfter(Node* node, Node* newNode) 
    {
        if (!node || !newNode) return;

        if (!node->right) {
            node->right = newNode;
            newNode->parent = node;
        } else {
            Node* successor = subtreeFirstHelper(node->right);
            successor->left = newNode;
            newNode->parent = successor;
        }
    }

    // insert a node before some node 
    void subtreeInsertBefore(Node* node, Node* newNode) 
    {
        if (!node || !newNode) return;

        if (!node->left) {
            node->left = newNode;
            newNode->parent = node;
        } else {
            Node* predecessor = subtreeLastHelper(node->left);
            predecessor->right = newNode;
            newNode->parent = predecessor;
        }
    }

    // delete a node
    void subtree_delete(Node* node)
    {
        if (!node) return;

        if (!node->left && !node->right) {
            if (node->parent) {
                if (node == node->parent->left) {
                    node->parent->left = nullptr;
                } else {
                    node->parent->right = nullptr;
                }
            } else {
                root = nullptr;
            }
            delete node;
            return;
        }

        if (node->left) {
            Node* predecessor = subtreeLastHelper(node->left);
            int temp = predecessor->val;
            predecessor->val = node->val;
            node->val = temp;
            subtree_delete(predecessor);
        } else if (node->right) {
            Node* successor = subtreeFirstHelper(node->right);
            int temp = successor->val;
            successor->val = node->val;
            node->val = temp;
            subtree_delete(successor);
        }
    }

    public: 
    // BST constructor 
    BST(): root(nullptr) {}

    // insert
    void insert(int val) 
    {
        root = insertHelper(root, val, nullptr);
    };

    // printout in-order traversal
    void inOrderTraverse()
    {
        inOrderTraverseHelper(root);
    }

    // return subtree left-most node
    Node* subtreeFirst(Node* node) 
    {
        return subtreeFirstHelper(node);
    }

    // return subtree right-most node
    Node* subtreeLast(Node* node) 
    {
        return subtreeLastHelper(node);
    } 
};

int main()
{
    BST tree;
    // choose a root
    tree.insert(6);
    
    // build the BST
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);

    // print in-order traversal 
    tree.inOrderTraverse();
    return 0;
}