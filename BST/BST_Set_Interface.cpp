#include <cstdio>
using namespace std;
// BST for a set interface

struct Node 
{
    int key;
    Node* left;
    Node* right;
    Node* parent;

    Node(int k): key(k), left(nullptr), right(nullptr), parent(nullptr) {} 
};

class BST 
{
    private:
    Node* root;
    
    Node* inserHelper(Node* node, int key, Node* parent=nullptr)
    {
        if (!node) {
            Node* newNode = new Node(key);
            newNode->parent = parent;
            return newNode;
        }

        if (node->key == key) return node;

        if (node->key > key) { 
            node->left = inserHelper(node->left, key, node);
        } else if (node->key < key) { 
            node->right = inserHelper(node->right, key, node);
        }
        return node;
    }

    Node* subtreeFindHelper(Node* node, int k)
    {
        if (!node) return nullptr;
        if (node->key == k) return node;
        if (node->key > k) return subtreeFindHelper(node->left, k);
        return subtreeFindHelper(node->right, k);
    }

    public:
    BST(): root(nullptr) {};

    void insert(int key) 
    {
        root = inserHelper(root, key, nullptr);
    }

    Node* subtreeFind(int k)
    {
        return subtreeFindHelper(root, k);
    }
};

int main()
{
    BST tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(0);
    tree.insert(7);
    tree.insert(2);
    tree.insert(3);

    Node* result = tree.subtreeFind(10);
    if (result) {
        printf("Found key: %d\n", result->key);
    }
}