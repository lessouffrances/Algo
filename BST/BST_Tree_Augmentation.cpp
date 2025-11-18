#include <climits>
#include <algorithm>
using namespace std;

struct Node
{
    int val;
    int size;
    int maxi;
    int sum;
    int height;
    Node* left;
    Node* right;
    Node* parent;

    Node(int x): val(x), size(1), maxi(x), sum(x), height(1), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BST
{
    private:
    Node* root;
    BST(): root(nullptr) {}

    Node* insertHelper(Node* node, int val, Node* parent=nullptr)
    {
        if (!node) {
            Node* newNode = new Node(val);
            newNode->parent = parent;
            return newNode;
        }

        if (node->val > val) {
            node->left = insertHelper(node->left, val, node);
        } else {
            node->right = insertHelper(node->right, val, node);
        }

        // maintain subtree properties
        updateProperties(node);

        // rebalance if needed
        node = subtreeRebalance(node);
        // Update root if this was the root
        if (!node->parent) {
            root = node;
        }
    
        return node;
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


    void subtreeInsertAfter(Node* node, Node* newNode) 
    {
        if (!node || !newNode) return;
        Node* insertionPoint;
        if (!node->right) {
            node->right = newNode;
            newNode->parent = node;
            insertionPoint = node;
        } else {
            Node* successor = subtreeFirstHelper(node->right);
            successor->left = newNode;
            newNode->parent = successor;
            insertionPoint = successor;
        }
        
        // Update and rebalance ALL ancestors
        Node* current = insertionPoint;
        while (current) {
            updateProperties(current);
            Node* newRoot = subtreeRebalance(current);
        
            // Update parent's pointer if rotation occurred
            if (newRoot != current) {
                if (newRoot->parent) {
                    if (newRoot->parent->left == current) {
                        newRoot->parent->left = newRoot;
                    } else {
                        newRoot->parent->right = newRoot;
                    }
                } else {
                    root = newRoot;
                }
                current = newRoot;
            }
            current = current->parent;
        }
    }

    // insert a node before some node 
    void subtreeInsertBefore(Node* node, Node* newNode)
    {
        if (!node || !newNode) return;
        Node* insertionPoint;
        
        if (!node->left) {
            node->left = newNode;
            newNode->parent = node;
            insertionPoint = node;
        } else {
            Node* predecessor = subtreeLastHelper(node->left);
            predecessor->right = newNode;
            newNode->parent = predecessor;
            insertionPoint = predecessor;
        }
        
        // Update and rebalance ALL ancestors
        Node* current = insertionPoint;
        while (current) {
            updateProperties(current);
            Node* newRoot = subtreeRebalance(current);
        
            // Update parent's pointer if rotation occurred
            if (newRoot != current) {
                if (newRoot->parent) {
                    if (newRoot->parent->left == current) {
                        newRoot->parent->left = newRoot;
                    } else {
                        newRoot->parent->right = newRoot;
                    }
                } else {
                    root = newRoot;
                }
                current = newRoot;  // ✓ Follow new structure after rotation
            }
            current = current->parent;
        }
    }

    // delete a node
    void subtree_delete(Node* node)
    {
        if (!node) return;

        if (!node->left && !node->right) {
            Node* parent = node->parent;
            if (parent) {
                if (node == parent->left) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
            } else {
                root = nullptr;
            }
            delete node;

            // Update and rebalance ancestors
            Node* current = parent;
            while (current) {
                updateProperties(current);
                Node* newRoot = subtreeRebalance(current);
                if (newRoot != current) {
                    if (newRoot->parent) {
                        if (newRoot->parent->left == current) {
                            newRoot->parent->left = newRoot;
                        } else {
                            newRoot->parent->right = newRoot;
                        }
                    } else {
                        root = newRoot;
                    }
                    current = newRoot;
                }
                current = current->parent;
            }
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

        //  After recursive delete, update THIS node and ALL ancestors
        Node* current = node;
        while (current) {
            updateProperties(current);
            Node* newRoot = subtreeRebalance(current);
            
            if (newRoot != current) {
                if (newRoot->parent) {
                    if (newRoot->parent->left == current) {
                        newRoot->parent->left = newRoot;
                    } else {
                        newRoot->parent->right = newRoot;
                    }
                } else {
                    root = newRoot;
                }
                current = newRoot;
            }
            current = current->parent;
        }
    }


    void updateProperties(Node* node)
    {
        if (!node) return;
        // update height
        int leftHeight = node->left ? node->left->height : 0;
        int rightHeight = node->right ? node->right->height : 0;
        node->height = 1 + max(leftHeight, rightHeight);

        // update size
        int leftSize = node->left ? node->left->size : 0;
        int rightSize = node->right ? node->right->size : 0;
        node->size = 1 + leftSize + rightSize;

        // update max
        int leftMax = node->left ? node->left->maxi : INT_MIN;
        int rightMax = node->right ? node->right->maxi : INT_MIN;
        node->maxi = max( {node-> val, leftMax, rightMax} );

        // udpate sum
        int leftSum = node->left ? node->left->sum : 0;
        int rightSum = node->right ? node->right->sum : 0;
        node->sum = node->val + leftSum + rightSum;
    }

    int skew(Node* node)
    {
        if (!node) return 0;

        int leftHeight = node->left ? node->left->height : 0;
        int rightHeight = node->right ? node->right->height : 0;
        return rightHeight - leftHeight;
    }

    Node* rotateRight(Node* X) {
        Node* Y = X->left;
        Node* B = Y->right;
        
        // update the changing edges
        Y->right = X;
        X->left = B;
        
        // Update parent pointers
        Y->parent = X->parent;
        X->parent = Y;
        if (B) B->parent = X;
        
        // Update parent's child pointer
        if (Y->parent) {
            if (Y->parent->left == X) {
                Y->parent->left = Y;
            } else {
                Y->parent->right = Y;
            }
        }
        
        // Update properties (X first since it's now lower)
        updateProperties(X);
        updateProperties(Y);
        
        return Y;
    }

    // Left rotation
    Node* rotateLeft(Node* X) {
        Node* Y = X->right;
        Node* B = Y->left;
        
        // update the changing edges
        Y->left = X;
        X->right = B;
        
        // Update parent pointers
        Y->parent = X->parent;
        X->parent = Y;
        if (B) B->parent = X;
        
        // Update parent's child pointer
        if (Y->parent) {
            if (Y->parent->left == X) {
                Y->parent->left = Y;
            } else {
                Y->parent->right = Y;
            }
        }
        
        // Update properties (X first since it's now lower)
        updateProperties(X);
        updateProperties(Y);
        
        return Y;
    }

    Node* subtreeRebalance(Node* X) {
        if (!X) return nullptr;
        
        int skewX = skew(X);
        
        // Balanced: no rebalancing needed
        if (skewX >= -1 && skewX <= 1) {
            return X;
        }
        
        // Right-heavy: skew >= 2
        if (skewX >= 2) {
            Node* Y = X->right;  // Right child must exist
            int skewY = skew(Y);
            
            // Case 1 & 2: skew(Y) >= 0 (right-right or right-balanced)
            // Solution: Single left rotation on X
            if (skewY >= 0) {
                return rotateLeft(X);
            }
            // Case 3: skew(Y) < 0 (right-left case)
            // Y is left-skewed
            // Solution: Right rotation on Y, then left rotation on X
            else {
                X->right = rotateRight(Y);
                return rotateLeft(X);
            }
        }
        
        // Left-heavy: skew <= -2
        if (skewX <= -2) {
            Node* Y = X->left;  // Left child must exist
            int skewY = skew(Y);
            
            // Case 1 & 2: skew(Y) <= 0 (left-left or left-balanced)
            // Solution: Single right rotation on X
            if (skewY <= 0) {
                return rotateRight(X);
            }
            // Case 3: skew(Y) > 0 (left-right case)
            // Y is right-skewed
            // Solution: Left rotation on Y, then right rotation on X
            else {
                X->left = rotateLeft(Y);
                return rotateRight(X);
            }
        }
        
        return X;
    }
};