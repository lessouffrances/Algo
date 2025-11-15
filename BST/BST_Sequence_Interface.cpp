struct Node 
{
    int val;
    Node* left;
    Node* right;
    Node* parent;

    Node(int x): val(x), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BST 
{
    private:
    Node* root;

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

    int sizeHelper(Node* node)
    {
        if(!node) return 0;
        return 1+sizeHelper(node->left)+sizeHelper(node->right);
    }

    Node* subtreeFindAtHelper(Node* node, int i)
    {
        if (!node) return nullptr;

        int nL = sizeHelper(node->left);
        if (i == nL) return node;

        if (i < nL) {
            return subtreeFindAtHelper(node->left, i);
        } else {
            return subtreeFindAtHelper(node->right, i-nL-1);
        }

    }

    public: 
    BST(): root(nullptr) {}

    void insert(int val) 
    {
        root = insertHelper(root, val, nullptr);
    }

    int size()
    {
        return sizeHelper(root);
    }

    Node* subtreeFindAt(int i)
    {
        if (i < 0 || i >= sizeHelper(root)) return nullptr;
        return subtreeFindAtHelper(root, i);
    }

    
};

int main()
{
    BST tree;

    tree.insert(5);
    tree.insert(0);
    tree.insert(10);
    tree.insert(1);
    tree.insert(9);
    tree.insert(2);
    tree.insert(8);
    tree.insert(3);
    tree.insert(7);






}