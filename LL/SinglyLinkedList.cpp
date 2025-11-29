struct Node
{
    int data; 
    Node* next;
    
    Node(int val): data(val), next(nullptr) {}
};

class SinglyLinkedList
{
    private:
    Node* head;

    public:
    SinglyLinkedList(): head(nullptr) {}

    ~SinglyLinkedList() 
    {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void insertFront(int val) 
    {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    void insertEnd(int val) 
    {
        Node* newNode = new Node(val);
        // if LL is empty
        if (head == nullptr) {
            head = newNode;
            return;
        }

        // if LL is not empty
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void deleteNode(int val)
    {
        // if LL is empty
        if (head == nullptr) return;

        // if head is the val to delete
        if (head->data == val) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        // others
        Node* current = head;
        while (currnt->next != nullptr && current->next->data != val) {
            current = current->next;
        }

        // found the val before LL ends
        if (current->next != nullptr) {
            Node* temp = current->next;
            current->next= current->next->next; // by pass the current->next, which is exactly the node we want to delete
            delete temp;
        }
    }

    bool search(int val)
    {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == val) return true;
            current = current->next;
        }
        return false;
    }
};

