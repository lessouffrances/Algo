using namespace std;

struct Node
{
    int val;
    Node* left;
    Node* right;
    Node* parent;

    Node(int x): val(v), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BST
{
    private:
    Node* root;
    BST(): root(nullptr) {};

    // private insert
    Node* insertHelper(Node* node, int val, Node* parent=nullptr) 
    {
        if(!node) {
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

    void inOrderTraverseHelper(Node* node) 
    {
        if (!node) return;

        inOrderTraverseHelper(node->left);
        printf("%d ", node->val);
        inOrderTraverseHelper(node->right);
    }

    Node* subtreeFirstHelper(Node* node) 
    {
        if (!node) return nullptr;

        while (node->left) {
            node = node->left;
        }
        return node;
    }

    Node* subtreeLastHelper(Node* node)
    {
        if (!node) return nullptr;

        while (node->right) {
            node = node->right;
        }
        return node;
    }

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

};
