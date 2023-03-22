// BST-app.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <fstream>
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

void run_tests(int iterations = 1, int unitDivisor = 1) {
    ofstream c_out("creation_times.txt");
    ofstream s_out("search_times.txt");
    ofstream h_out("tree_heights.txt");
    // c_out.precision(17); if result gets rounded use it

    c_out << "size;Cb;Cta;Ctb\n";
    s_out << "size;Sa;Sb;Sta;Stb\n";
    h_out << "size;Hta;Htb\n";

    srand(time(0));

    for (int n = 1000; n < 30001; n += 1000) {
        //display and write n
        cout << "n: " << n;
        c_out << n << ";";
        s_out << n << ";";
        h_out << n << ";";

        double Cb = 0.0, Cta = 0.0, Ctb = 0.0, Sa = 0.0, Sb = 0.0, Sta = 0, Stb = 0;
        int Hta = 0, Htb = 0;

        for (int iter = 0; iter < iterations; iter++)
        {
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
            Cb += chrono::duration_cast<chrono::nanoseconds>(end - start).count();

            //measure Sa
            for (int i = 0; i < n; i++) {
                int x = arrB[i];
                start = chrono::steady_clock::now();
                simple_search(arrA, n, x);
                end = chrono::steady_clock::now();
                Sa += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            }

            //measure Sb
            for (int i = 0; i < n; i++) {
                int x = arrA[i];
                start = chrono::steady_clock::now();
                binary_search(arrB, 0, n, x);
                end = chrono::steady_clock::now();
                Sb += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            }

            //measure Cta + Hta
            start = chrono::steady_clock::now();
            BST ta;
            for (int i = 0; i < n; i++) {
                ta.insert(arrA[i]);
            }
            end = chrono::steady_clock::now();
            Cta += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            Hta += ta.get_height();

            //create mid array
            int* arrC = new int[n];
            for (int i = 0; i < n; i++) {
                arrC[i] = -1;
            }
            add_mid_element(arrC, arrB, n);

            //measure Ctb + Htb
            start = chrono::steady_clock::now();
            BST tb;
            for (int i = 0; i < n; i++) {
                tb.insert(arrC[i]);
            }
            end = chrono::steady_clock::now();
            Ctb += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            Htb += tb.get_height();

            //measure Sta
            for (int i = 0; i < n; i++) {
                int x = arrA[i];
                start = chrono::steady_clock::now();
                ta.search(x);
                end = chrono::steady_clock::now();
                Sta += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            }

            //measure Stb
            for (int i = 0; i < n; i++) {
                int x = arrA[i];
                start = chrono::steady_clock::now();
                tb.search(x);
                end = chrono::steady_clock::now();
                Stb += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            }

            delete[]arrA;
            delete[]arrB;
            delete[]arrC;
            cout << " | ";
        }
        Cb /= iterations * unitDivisor;
        Ctb /= iterations * unitDivisor;
        Cta /= iterations * unitDivisor;

        Sa /= iterations * unitDivisor;
        Sb /= iterations * unitDivisor;
        Sta /= iterations * unitDivisor;
        Stb /= iterations * unitDivisor;

        Hta /= iterations;
        Htb /= iterations;

        // output results
        c_out << Cb << ";";
        c_out << Cta << ";";
        c_out << Ctb << ";";

        s_out << Sa << ";";
        s_out << Sb << ";";
        s_out << Sta << ";";
        s_out << Stb << ";";
        
        h_out << Hta << ";";
        h_out << Htb << ";";

        c_out << "\n";
        s_out << "\n";
        h_out << "\n";
        
        cout << endl;
    }

    c_out.close();
    s_out.close();
    h_out.close();
}

int main()
{
    //the code
    run_tests(10, 1000000);

    return 0;
}

