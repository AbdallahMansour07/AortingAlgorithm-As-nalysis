#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

// ========== Bubble Sort ==========
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

// ========== Merge Sort ==========
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; ++i) L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// ========== Quick Sort ==========
int partition(int arr[], int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j] < pivot)
            swap(arr[++i], arr[j]);
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ========== ÊæáíÏ ÈíÇäÇÊ ==========
void generateRandom(int arr[], int size) {
    for (int i = 0; i < size; ++i)
        arr[i] = rand() % 10000;
}

void generatePartiallySorted(int arr[], int size) {
    generateRandom(arr, size);
    sort(arr, arr + size / 2);
}

void generateReversed(int arr[], int size) {
    for (int i = 0; i < size; ++i)
        arr[i] = size - i;
}

// ========== äÓÎ ãÕÝæÝÉ ==========
void copyArray(int from[], int to[], int size) {
    for (int i = 0; i < size; ++i)
        to[i] = from[i];
}

// ========== ÊÌÑÈÉ ÇáÊäÝíÐ ==========
void runTrial(int input[], int size, const string& label) {
    int* arr = new int[size];
    double bubbleTimes[3] = {0}, mergeTimes[3] = {0}, quickTimes[3] = {0};

    for (int run = 0; run < 3; ++run) {
        copyArray(input, arr, size);
        clock_t start = clock();
        bubbleSort(arr, size);
        clock_t end = clock();
        bubbleTimes[run] = double(end - start) / CLOCKS_PER_SEC;

        copyArray(input, arr, size);
        start = clock();
        mergeSort(arr, 0, size - 1);
        end = clock();
        mergeTimes[run] = double(end - start) / CLOCKS_PER_SEC;

        copyArray(input, arr, size);
        start = clock();
        quickSort(arr, 0, size - 1);
        end = clock();
        quickTimes[run] = double(end - start) / CLOCKS_PER_SEC;
    }

    double bubbleAvg = (bubbleTimes[0] + bubbleTimes[1] + bubbleTimes[2]) / 3;
    double mergeAvg = (mergeTimes[0] + mergeTimes[1] + mergeTimes[2]) / 3;
    double quickAvg = (quickTimes[0] + quickTimes[1] + quickTimes[2]) / 3;

    cout << "\n=== " << label << " ===\n";
    cout << "Bubble Sort Times: " << bubbleTimes[0] << ", " << bubbleTimes[1] << ", " << bubbleTimes[2] << " seconds\n";
    cout << "Merge Sort Times: " << mergeTimes[0] << ", " << mergeTimes[1] << ", " << mergeTimes[2] << " seconds\n";
    cout << "Quick Sort Times: " << quickTimes[0] << ", " << quickTimes[1] << ", " << quickTimes[2] << " seconds\n";
    cout << "Averages:\n";
    cout << "Bubble Sort Avg: " << bubbleAvg << " seconds\n";
    cout << "Merge Sort Avg: " << mergeAvg << " seconds\n";
    cout << "Quick Sort Avg: " << quickAvg << " seconds\n";

    delete[] arr;
}

int main() {
    const int size = 1000;
    int* data = new int[size];
    srand(time(0));

    generateRandom(data, size);
    runTrial(data, size, "Random Data");

    generatePartiallySorted(data, size);
    runTrial(data, size, "Partially Sorted Data");

    generateReversed(data, size);
    runTrial(data, size, "Reversed Data");

    delete[] data;
    return 0;
}