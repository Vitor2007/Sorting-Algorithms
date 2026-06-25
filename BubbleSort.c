#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <x86intrin.h>
int main(){
int i, j, temp;//auxiliary variable for the loops and element exchange 
uint64_t start, end; // variables used to the measurement of amount of CPU clock ticks were consumed in the process
int vector[10000] = {};// Array to be sorted (the size of the array can be  changed according to current need)

    
start = __rdtsc();// Starts the timer(measurement based on amount of CPU clock ticks)
   
    for (i = 0; i < 10000 - 1; i++) {          // External loop of Bubble sort:controls the number iterations in the array 
                                                // Note that it is limited to 10000 since it is the size of the array
        // Internal loop: compares the adjacent element and throws the greater element to the end
        // For very iteration of 'i' , the greatest element "floats" to it's correct position 
        for (j = 0; j < 10000 - i - 1; j++) { //Note that it is limited to 10000 since it is the size of the array, if the size of the array is different , the limit must be changed accordingly

            if (vector[j] > vector[j + 1]) { // If the current element  is greater  than the next one, they exchange places 
                temp = vector[j];
                vector[j] = vector[j + 1];
                vector[j + 1] = temp;
            }
        }
    }
    
     end = __rdtsc();// Ends the timer
      
    for(int i = 0; i < 10000; i++) {  // Prints the sorted array , note that it is limited to 10000 since it is the size of the array, if the size of the array is different , the limit must be changed accordingly
    printf("%d ", vector[i]);
    
    }
    printf("\nCPU clock ticks consumed: %lu\n", (end - start)); // Prints the amount of CPU clock ticks consumed in the process of sorting the array
  
  
  
  }