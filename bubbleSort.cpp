#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;

void bubble(int *, int);
void swap(int &, int &);

// Bubble Sort function
void bubble(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {  	 
        int first = i % 2; // even or odd pass

        #pragma omp parallel for shared(a, first)
        for (int j = first; j < n - 1; j += 2)
        {  	 
            if (a[j] > a[j + 1])
            {  	 
                swap(a[j], a[j + 1]);
            }  	 
        }  	 
    }
}

// Swap function
void swap(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

// Main function
int main()
{
    int *a, n;
    cout << "\nEnter total number of elements => ";
    cin >> n;
    a = new int[n];

    cout << "\nEnter elements => ";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    
    bubble(a, n);
    
    cout << "\nSorted array is => ";
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << endl;
    }

    delete[] a; // Always free dynamically allocated memory

    return 0;
}
