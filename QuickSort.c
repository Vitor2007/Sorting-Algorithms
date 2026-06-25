#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <x86intrin.h>
uint64_t start, end; // Global variables to store timestamps of the clock cycle of CPU 
void exchange(int *a, int *b) {  // Auxiliary function to exchange the value of two variables using pointers
    int t = *a;
    *a = *b;
    *b = t;
}

// Partitioning function: Chooses a pivot e makes that the array has the smaller elements in the left and greater elements in the right of the pivot 
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Chooses the last elements as the pivot 
    int i = (low - 1); //  Index of the smallest element (points out the correct position of the pivot at the moment) 

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {     // Compares each element of the arrray with the pivot
            i++;                  // If the current element is smaller than the pivot,moves it to the left region of the array
            exchange(&arr[i], &arr[j]); // Increments the index of the smallest element
        }
    }
    exchange(&arr[i + 1], &arr[high]);  // Puts the pivot in the correct position (right after the last element smaller than the pivot)
    return (i + 1);     // return to the position of the pivot
}
// recursive implementation of the quick sorting algorithm 
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // pi is the index do partitioning, arr[pi] already in the right position
        quickSort(arr, low, pi - 1);   //Recursively sorts the elements before and after partitioning 
        quickSort(arr, pi + 1, high);
    }
}

// Prints array
void ArrayPrint(int arr[], int tmn) {
    for (int i = 0; i < tmn; i++)   
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    
    int data[100000] = {}; // Array to be sorted (size can change according to current need)

    for(int i = 99999; i > -1; i--){
        data[i] = i;
    }
                        int n = sizeof(data) / sizeof(data[0]);// Gets the size of the array
    
    printf("Original Array: \n");

    
    start = __rdtsc();// Starts timer(measured in CPU clock ticks)
    
    quickSort(data, 0, n - 1);// Calls the sorting function
    
   end = __rdtsc();   // Finishes the timer

    ArrayPrint(data, n); // Calls the function to print the sorted array
    printf("Sorted array: \n");
    

    printf("CPU clock ticks consumed: %llu\n", (end - start));//Prints how many CPU clock ticks were consumed
    return 0;
}
