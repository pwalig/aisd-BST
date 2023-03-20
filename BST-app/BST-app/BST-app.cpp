// BST-app.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <time.h>
#include <chrono>
#include <cmath>
#include "BST.h"
using namespace std;


void display_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

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

bool contains(int arr[], int n, int key) {
    if (n == 0)
        return false;
    for (int i = 0; i < n; i++) {
        if (arr[i] == key)
            return true;
    }
    return false;
}

int* generateArray(int n) {
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        int x = rand() % n;
        while (contains(arr, i, x))
            x = rand() % n;
        arr[i] = x;
    }
    return arr;
}

int simple_search(int arr[], int n, int key) {
    int i = 0;
    while(i < n && arr[i] != key) {
        i++;
    }
    if (i == n)
        return -1;
    return arr[i];
}

int binary_search(int arr[], int l, int r, int x)
{
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] == x)
            return m;

        if (arr[m] < x)
            l = m + 1;

        else
            r = m - 1;
    }
    return -1;
}

void add_mid_element(int mod_a[], int arr[], int n, int l = 0, int r = -10) {
    if (r == -10)
        r = n-1;
    if (l <= r) {
        int m = l + (r - l) / 2;
        int i = 0;
        while (mod_a[i] != -1)
            i++;
        mod_a[i] = arr[m];
        add_mid_element(mod_a, arr, n, l, m - 1);
        add_mid_element(mod_a, arr, n, m + 1, r);
    }
}

void run_tests() {
    srand(time(0));
    for (int n = 20; n < 25; n += 1) {
        cout << "n: " << n << endl;
        //generate A
        int* arrA;
        arrA = generateArray(n);

        //measure Cb
        auto start = chrono::steady_clock::now();
        int* arrB = new int[n];
        for (int i = 0; i < n; i++) {
            arrB[i] = arrA[i];
        }
        quickSort(arrB, 0, n - 1);
        auto end = chrono::steady_clock::now();
        cout << "Cb: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;

        //measure Sa
        double time_sa = 0;
        for (int i = 0; i < n; i++) {
            int x = arrB[i];
            start = chrono::steady_clock::now();
            simple_search(arrA, n, x);
            end = chrono::steady_clock::now();
            time_sa += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        }
        cout << "Sa: " << time_sa << "ns\n";

        //measure Sb
        double time_sb = 0;
        for (int i = 0; i < n; i++) {
            int x = arrA[i];
            start = chrono::steady_clock::now();
            binary_search(arrB, 0, n, x);
            end = chrono::steady_clock::now();
            time_sb += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        }
        cout << "Sb: " << time_sb << "ns\n";

        //measure Cta
        start = chrono::steady_clock::now();
        BST ta;
        for (int i = 0; i < n; i++) {
            ta.insert(arrA[i]);
        }
        end = chrono::steady_clock::now();
        double time_cta = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        cout << "Cta: " << time_cta << "ns\n";
        cout << "height: " << ta.get_height() << endl;
        ta.display(BST::Preorder);


        //BROKEN
        //create mid array
        int* arrC = new int[n];
        for (int i = 0; i < n; i++) {
            arrC[i] = -1;
        }
        add_mid_element(arrC, arrB, n);
        display_array(arrC, n);

        //measure Ctb 
        start = chrono::steady_clock::now();
        BST tb;
        for (int i = 0; i < n; i++) {
            tb.insert(arrC[i]);
        }
        end = chrono::steady_clock::now();
        double time_ctb = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        cout << "Ctb: " << time_cta << "ns\n";
        cout << "height: " << tb.get_height() << endl;
        tb.display(BST::Preorder);

        cout << endl;

        delete[]arrA;
        delete[]arrB;
        delete[]arrC;
    }
}

int main()
{
    //the code
    run_tests();

    return 0;
}

