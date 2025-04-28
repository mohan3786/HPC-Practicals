#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;

void mergesort(int a[], int i, int j);
void merge(int a[], int i1, int j1, int i2, int j2);

void mergesort(int a[], int i, int j)
{
    int mid;
    if (i < j)
    {
        mid = (i + j) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergesort(a, i, mid);
            }

            #pragma omp section
            {
                mergesort(a, mid + 1, j);
            }
        }

        merge(a, i, mid, mid + 1, j);
    }
}

void merge(int a[], int i1, int j1, int i2, int j2)
{
    int* temp = new int[j2 - i1 + 1];  // Dynamically allocate memory
    int i = i1, j = i2, k = 0;

    while (i <= j1 && j <= j2)
    {
        if (a[i] < a[j])
        {
            temp[k++] = a[i++];
        }
        else
        {
            temp[k++] = a[j++];
        }
    }

    while (i <= j1)
    {
        temp[k++] = a[i++];
    }

    while (j <= j2)
    {
        temp[k++] = a[j++];
    }

    for (i = i1, j = 0; i <= j2; i++, j++)
    {
        a[i] = temp[j];
    }

    delete[] temp;  // Free dynamically allocated memory
}

int main()
{
    int *a, n, i;
    cout << "\nEnter total number of elements => ";
    cin >> n;
    a = new int[n];

    cout << "\nEnter elements => ";
    for (i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    double start_time = omp_get_wtime();  // Start timer

    mergesort(a, 0, n - 1);

    double end_time = omp_get_wtime();    // Stop timer
    cout << "\nSorted array is => ";
    for (i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }

    cout << "\nTime taken for parallel merge sort: " << end_time - start_time << " seconds." << endl;

    delete[] a;  // Free dynamically allocated memory
    return 0;
}
