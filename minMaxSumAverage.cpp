#include <iostream>
#include <omp.h>
#include <climits>
using namespace std;

// Function to compute minimum value using parallel reduction
void min_reduction(int arr[], int n) {
  int min_value = INT_MAX;  // Initialize min_value to the maximum possible integer value
  
  // Parallel for loop with reduction on 'min_value' to safely find the minimum
  #pragma omp parallel for reduction(min: min_value)
  for (int i = 0; i < n; i++) {
    if (arr[i] < min_value) {
      min_value = arr[i];  // Update min_value if current element is smaller
    }
  }
  
  cout << "Minimum value: " << min_value << endl;  // Output the minimum value
}

// Function to compute maximum value using parallel reduction
void max_reduction(int arr[], int n) {
  int max_value = INT_MIN;  // Initialize max_value to the minimum possible integer value
  
  // Parallel for loop with reduction on 'max_value' to safely find the maximum
  #pragma omp parallel for reduction(max: max_value)
  for (int i = 0; i < n; i++) {
    if (arr[i] > max_value) {
      max_value = arr[i];  // Update max_value if current element is larger
    }
  }
  
  cout << "Maximum value: " << max_value << endl;  // Output the maximum value
}

// Function to compute sum using parallel reduction
void sum_reduction(int arr[], int n) {
  int sum = 0;  // Initialize sum to 0
  
  // Parallel for loop with reduction on 'sum' to compute total sum of elements
  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < n; i++) {
    sum += arr[i];  // Add the current element to the sum
  }
  
  cout << "Sum: " << sum << endl;  // Output the total sum of elements
}

// Function to compute average using parallel reduction
void average_reduction(int arr[], int n) {
  int sum = 0;  // Initialize sum to 0
  
  // Parallel for loop with reduction on 'sum' to compute total sum of elements
  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < n; i++) {
    sum += arr[i];  // Add the current element to the sum
  }
  
  // Calculate and output the average (divide by n, not n-1 as we want the average of all elements)
  cout << "Average: " << (double)sum / n << endl;  
}

int main() {
    int *arr, n;
    
    // Take input for the number of elements in the array
    cout << "\nEnter total number of elements => ";
    cin >> n;
    
    // Dynamically allocate memory for the array
    arr = new int[n];
    
    // Take input for each element in the array
    cout << "\nEnter elements => ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];  // Input array elements one by one
    }

    // Call the functions to calculate min, max, sum, and average using parallel reduction
    min_reduction(arr, n);
    max_reduction(arr, n);
    sum_reduction(arr, n);
    average_reduction(arr, n);

    // Free dynamically allocated memory
    delete[] arr; 
    
    return 0;
}
