Multithreaded Sorting Algorithms in C++
Description
This C++ program demonstrates and compares the performance of single-threaded and multithreaded versions of two classic sorting algorithms:
Merge Sort and Quick Sort

The program generates a list of random integers, sorts them using each algorithm variant, and measures the execution time for each approach.

Features
Random integer array generation
Single-threaded Merge Sort
Multithreaded Merge Sort using std::thread
Single-threaded Quick Sort
Multithreaded Quick Sort using std::thread
Time measurement using std::chrono
Clear comparison of sorting results and performance

The user inputs the number of integers to sort. The program then generates that many random integers (between 1 and 10,000), and runs all four sorting implementations: 
Merge Sort (single-threaded), Merge Sort (multithreaded), Quick Sort (single-threaded), and Quick Sort (multithreaded). 
After sorting, it prints the sorted arrays and the time taken for each algorithm in milliseconds.
Execution time is recorded for each method.

All sorted arrays and their respective execution times are displayed.
