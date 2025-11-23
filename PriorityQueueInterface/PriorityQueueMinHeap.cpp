// Priority Queue Interface:
// .top() -> return the top element
// .pop() -> remove and return the top element
// .push() -> add element into the queue
// .empty() -> see if the queue is empty
// .size() -> return the number of elements in the queue
// .clear() -> clear the queue

#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <stdexcept>

using namespace std;

template<typename T>
class priority_queue
{
    private:
    vector<T> heap;

    int parent(int i) { return (i-1)/2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void minHeapifyDown(int i)
    {
        int smallest = i;
        int left = leftChild(i);
        int right = rightChild(i);
        int n = heap.size();

        if (left < n && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < n && heap[right] < heap[smallest]) {
            smallest = right;
        }

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            minHeapifyDown(smallest);
        }
    }

    void minHeapifyUp(int i)
    {
        if (i == 0) return;
        int p = parent(i);

        if (heap[p] > heap[i]) {
            swap(heap[p], heap[i]);
            minHeapifyUp(p);
        }
    }

    public:
    T top() const
    {
        if (heap.empty()) {
            throw runtime_error("Priority queue is empty");
        }

        return heap[0];
    }

    T pop() 
    {
        if (heap.empty()) {
            throw runtime_error("Priority queue is empty");
        }

        T minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty()) {
            minHeapifyDown(0);
        }

        return minVal;
    }

    void push(const T& element) 
    {
        heap.push_back(element);
        minHeapifyUp(heap.size()-1);
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