// BST-app.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <time.h>
#include <chrono>
#include "BST.h"
using namespace std;


int partition(int arr[], int start, int end)
{

    int pivot = arr[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (arr[i] <= pivot) {
            i++;
        }

        while (arr[j] > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

void quickSort(int arr[], int start, int end)
{
    if (start >= end)
        return;
    int p = partition(arr, start, end);
    quickSort(arr, start, p - 1);
    quickSort(arr, p + 1, end);
}

int* generateArray(int n) {
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand()%n;
    }
    return arr;
}

int main()
{
    // BST demo
    BST t;
    t.insert(20);
    t.insert(25);
    t.insert(15);
    t.insert(10);
    t.insert(30);
    t.display();
    t.remove(20);
    t.display();
    t.remove(25);
    t.display();
    t.remove(30);
    t.display();

    // generate array and quicksort test
    srand(time(0));
    int *arrA;
    int n = 10;
    arrA = generateArray(n);
    //arrA = arrB;

    cout << endl;

    auto start = chrono::steady_clock::now();


    int *arrB = new int[n];
    for (int i = 0; i < n; i++) {
        arrB[i] = arrA[i];
        cout << arrA[i] << " ";
    }

    cout << endl;
    quickSort(arrB, 0, n - 1);

    auto end = chrono::steady_clock::now();

    cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;

    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << arrB[i] << " ";
    }

    delete[]arrA;
    delete[]arrB;
    return 0;
}

