// Max Heap Solution 
// void buildMaxHeapBottomUp(vector<int>& arr);
// void maxHeapifyDown(vector<int>& arr, int i, int n);
// void maxHeapifyUp(vector<int>& arr, int i, int n);
// void insert(vector<int>& arr, int x);
// int deleteMax(vector<int>& arr);
// int findMax(vector<int>& arr);
// void maxHeapSort(vector<int> arr);

#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

class MaxHeapSolution 
{
    
    // build max heap
    void buildMaxHeapBottomUp(vector<int>& arr)
    {
        if (arr.empty()) return;
        int n = arr.size();
        // start from the middle, and use maxHeapifyDown
        for (int i=n/2-1; i>=0; i--) {
            maxHeapifyDown(arr, i, n);
        }
    }


    void maxHeapifyDown(vector<int>& arr, int i, int n)
    {
        int largest = i;
        int left = 2*i+1, right = 2*i+2;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(arr[largest], arr[i]);
            maxHeapifyDown(arr, largest, n);
        }
    }


    void maxHeapifyUp(vector<int>& arr, int i, int n)
    {
        if (i == 0) return;
        int parent = (i-1)/2;
        if (arr[parent] < arr[i]) {
            swap(arr[parent], arr[i]);
            maxHeapifyUp(arr, parent, n);
        }
    }

    // insert
    void insert(vector<int>& arr, int x) 
    {
        // attach the leaf at the n-1 pos
        arr.push_back(x);

        // maxHeapifyUp the element
        int i = arr.size()-1;
        maxHeapifyUp(arr, i, arr.size());
    }

    // delete max
    int deleteMax(vector<int>& arr)
    {
        if (arr.empty()) return -1;

        int maxVal = arr[0];
        arr[0] = arr.back();
        arr.pop_back();

        if(!arr.empty()) {
            maxHeapifyDown(arr, 0, arr.size());
        }

        return maxVal;
    }

    // find max
    int findMax(vector<int>& arr)
    {
        if (arr.empty()) return -1;

        int maxVal = arr[0];
        return maxVal;
    }


    // max heap sort
    void maxHeapSort(vector<int>& arr) 
    {
        if (arr.empty()) {
            return;
        }

        // build max heap in-place
        buildMaxHeapBottomUp(arr);

        // swap and heapify down 
        int n = arr.size();
        for (int i=n-1; i>=0; i--) {
            swap(arr[i], arr[0]);
            maxHeapifyDown(arr, 0, i);
        }
    }


    void printVec(vector<int> arr)
    {
        for (int i=0; i<arr.size(); i++) {
            if (i == arr.size()-1) {
                printf("%d\n", arr[i]);
                return;
            }
            printf("%d ", arr[i]);
        }
    }
};

int main()
{
    vector<int> arr = {3, 5, 1, 8, 9, 2, 7, 4, 6};
    MaxHeapSolution solution = MaxHeapSolution();

    // build binary heap in arr in-place
    solution.buildMaxHeapBottomUp(arr);
    solution.printVec(arr);

    // insert new to the binaryHeap arr
    solution.insert(arr, 11);
    solution.printVec(arr);

    // delete max
    int maxVal = solution.deleteMax(arr);
    printf("The max element is %d\n", maxVal);
    printf("The arr after deleteMax: \n");
    solution.printVec(arr);


    vector<int> arrr = {3, 5, 1, 8, 9, 2, 7, 4, 6};
    solution.maxHeapSort(arrr);
    solution.printVec(arrr);
}