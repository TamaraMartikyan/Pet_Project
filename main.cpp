
#include <iostream>
#include <vector>
#include <thread>
#include <chrono> //time
#include <cstdlib> //rand()
#include <ctime>

using namespace std;
using namespace chrono;

// Merge Sort

void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (arr[i] < arr[j])
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }

    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    for (int k = 0; k < temp.size(); ++k)
        arr[left + k] = temp[k];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void ThreadMergeSort(vector<int>& arr, int left, int right, int depth = 0) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    if (depth >= 1) {
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
    }
    else {
        thread t1(ThreadMergeSort, ref(arr), left, mid, depth + 1);

        thread t2(ThreadMergeSort, ref(arr), mid + 1, right, depth + 1);
       
        t1.join();
        t2.join();
    }

    merge(arr, left, mid, right);
}

// Quick Sort 

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low >= high) return;

    int pi = partition(arr, low, high);
    
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
}

void ThreadQuickSort(vector<int>& arr, int low, int high, int depth = 0) {
    if (low >= high) return;

    int pi = partition(arr, low, high);

    if (depth >= 1) {
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
    else {
        thread t1(ThreadQuickSort, ref(arr), low, pi - 1, depth + 1);
        thread t2(ThreadQuickSort, ref(arr), pi + 1, high, depth + 1);
       
        t1.join();
        t2.join();
    }
}



void printArray(const vector<int>& arr) {
    for (int x : arr)
      cout << x << " ";
    cout << endl;
}



int main() {
    int n;
    cout << "How many numbers do you want to sort? ";
    cin >> n;

    srand(time(0));
    vector<int> originalArr(n);
    for (int i = 0; i < n; ++i)
        originalArr[i] = rand() % 10000 + 1; // random numbers

    cout << "\nGenerated numbers:\n";
    printArray(originalArr);


    // Single-thread Merge Sort
    vector<int> arr1 = originalArr;
    auto start1 = high_resolution_clock::now();
   
  mergeSort(arr1, 0, n - 1);
    auto end1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(end1 - start1).count();


    // Multithread 
    vector<int> arr2 = originalArr;
    auto start2 = high_resolution_clock::now();
    ThreadMergeSort(arr2, 0, n - 1);
    auto end2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(end2 - start2).count();


    // Single-thread Quick Sort
    vector<int> arr3 = originalArr;
    auto start3 = high_resolution_clock::now();
    quickSort(arr3, 0, n - 1);
    auto end3 = high_resolution_clock::now();
    auto duration3 = duration_cast<milliseconds>(end3 - start3).count();


    // Multithread 
    vector<int> arr4 = originalArr;
    auto start4 = high_resolution_clock::now();
    ThreadQuickSort(arr4, 0, n - 1);
    auto end4 = high_resolution_clock::now();
    auto duration4 = duration_cast<milliseconds>(end4 - start4).count();


    cout << "\nSorted array (Single-threaded Merge Sort): ";
    printArray(arr1);

    cout << "Sorted array (Multithreaded Merge Sort):   ";
    printArray(arr2);

    cout << "Sorted array (Single-threaded Quick Sort): ";
    printArray(arr3);

    cout << "Sorted array (Multithreaded Quick Sort):   ";
    printArray(arr4);

    cout << "\nTime taken (Single-threaded Merge Sort): " << duration1 << " ms\n";
    cout << "Time taken (Multithreaded Merge Sort):   " << duration2 << " ms\n";
    cout << "Time taken (Single-threaded Quick Sort): " << duration3 << " ms\n";
    cout << "Time taken (Multithreaded Quick Sort):   " << duration4 << " ms\n";

    return 0;
}
