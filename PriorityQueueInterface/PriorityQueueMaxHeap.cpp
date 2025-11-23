// Priority Queue Interface
// .top() -> return the maxi
// .pop() -> return and delete the maxi
// .push() -> add element to the queue
// .empty() -> check if the queue is empty
// .size() -> return the number of elements in the queue
// .clear() -> clear the queue

template <typename T>
class priority_queue
{
    private:
    vector<T> heap;

    int parent(int i) { return (i-1)/2; }
    int leftChild(int i) { return 2*i+1; }
    int rightChild(int i) { return 2*i+2; }

    void maxHeapifyDown(int i)
    {
        int largest = i;
        int left = leftChild(i);
        int right = rightChild(i);
        int n = heap.size();

        if (left < n && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < n && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(heap[largest], heap[i]);
            maxHeapifyDown(largest);
        }
    }

    void maxHeapifyUp(int i)
    {
        if (i == 0) return;
        int p = parent(i);

        if (heap[i] > heap[p]) {
            swap(heap[i], heap[p]);
            maxHeapifyUp(p);
        }
    }

    public:

    T top() const
    {
        if (heap.empty()) {
            throw runtime_error("Priority queue is empty.");
        }

        return heap[0];
    }

    T pop()
    {
        if (heap.empty()) {
            throw runtime_error("Priority queue is empty.");
        }

        T maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty()) {
            maxHeapifyDown(0);
        }

        return maxVal;
    }

    void push(const T& element)
    {
        heap.push_back(element);
        maxHeapifyUp(heap.size()-1);
    }

    bool empty() const
    {
        return heap.empty();
    }

    int size() const
    {
        return heap.size();
    }

    void clear() 
    {
        heap.clear();
    }

};