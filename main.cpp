
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;
using namespace chrono;

// Merge function
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (arr[i] < arr[j])
            temp.push_back(arr[i++]);4;
        else
            temp.push_back(arr[j++]);
    }
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    for (int k = 0; k < temp.size(); ++k)
        arr[left + k] = temp[k];
}

// Merge sort (recursive)
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Multithreaded version of merge sort
void parallelMergeSort(vector<int>& arr, int left, int right, int depth = 0) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    if (depth >= 1) { // Use only 2 threads (adjust as needed)
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
    }
    else {
        thread t1(parallelMergeSort, ref(arr), left, mid, depth + 1);
        thread t2(parallelMergeSort, ref(arr), mid + 1, right, depth + 1);
        t1.join();
        t2.join();
    }

    merge(arr, left, mid, right);
}

// Utility: Print array
void printArray(const vector<int>& arr) {
    for (int x : arr)
        cout << x << " ";
    cout << endl;
}

// Main function
int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> originalArr(n);
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; ++i)
        cin >> originalArr[i];

    // ---------- Single-threaded sort ----------
    vector<int> arr1 = originalArr;
    auto start1 = high_resolution_clock::now();
    mergeSort(arr1, 0, n - 1);
    auto end1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(end1 - start1).count();

    // ---------- Multithreaded sort ----------
    vector<int> arr2 = originalArr;
    auto start2 = high_resolution_clock::now();
    parallelMergeSort(arr2, 0, n - 1);
    auto end2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(end2 - start2).count();

    // ---------- Output ----------
    cout << "\nSorted Array (Single-threaded): ";
    printArray(arr1);

    cout << "Sorted Array (Multithreaded):   ";
    printArray(arr2);

    cout << "\nTime taken (Single-threaded): " << duration1 << " ms";
    cout << "\nTime taken (Multithreaded):   " << duration2 << " ms\n";

    return 0;
}
