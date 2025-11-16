// Min Heap Solution 
// void buildMinHeapBottomUp(vector<int>& arr);
// void minHeapifyDown(vector<int>& arr, int i, int n);
// void minHeapifyUp(vector<int>& arr, int i, int n);
// void insert(vector<int>& arr, int x);
// int deleteMin(vector<int>& arr);
// int findMin(vector<int>& arr);
// void minHeapSort(vector<int> arr);
#include <vector>
#include <algorithm>
#include <cstdio>

class MinHeapSolution 
{
    public:
    void buildMinHeapBottomUp(vector<int>& arr)
    {
        if (arr.empty()) return;
        int n = arr.size();

        for (int i=n/2-1; i>=0 i--) {
            minHeapifyDown(arr, i, n);
        }
    }

    void minHeapifyDown(vector<int>& arr, int i, int n)
    {
        int smallest = i;
        int left = 2*i+1, right = 2*i+2;

        if (left < n && arr[left] > arr[smallest]) {
            smallest = left;
        }

        if (right < n && arr[right] > arr[smallest]) {
            smallest = right;
        }

        if (smallest != i) {
            swap(arr[smallest], arr[i]);
            minHeapifyDown(arr, smallest, n);
        }
    }

    void minHeapifyUp(vector<int>& arr, int i, int n)
    {
        if (i == 0) return;
        int parent = (i-1)/2;
        if (arr[parent] > arr[i]) {
            swap(arr[parent], arr[i]);
            minHeapifyUp(arr, parent, n);
        }
    }

    void insert(vector<int>& arr, int x)
    {
        arr.push_back(x);
        int i = arr.size()-1;

        minHeapifyUp(arr, i, arr.size());
    }

    int deleteMin(vector<int>& arr)
    {
        if (arr.empty()) return -1;

        int minVal = arr[0];
        arr[0] = arr.back();
        arr.pop_back();

        if (!arr.empty()) {
            minHeapifyDown(arr, 0, arr.size());
        }
    }

    int findMin(vector<int>& arr)
    {
        if (arr.empty()) return -1;

        int minVal = arr[0];
        return minVal;
    }

    void minHeapSort(vector<int>& arr)
    {
        if (arr.empty()) return;

        // obtain a minHeap
        buildMinHeapBottomUp(arr);

        // deleteMin logic
        int n = arr.size();
        for (int i=n-1; i>=0; i--) {
            swap(arr[0], arr[i]);
            minHeapifyDown(arr, 0, i);
        }
        // this will give a descending order array
    }
};