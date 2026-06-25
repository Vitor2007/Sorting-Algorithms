#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <x86intrin.h>
void mergesort(int *v, int n);
void sort(int *v, int *c, int i, int f); //Pre-declaration of functions to avoid implicit declaration warnings
void merge(int *v, int *c, int i, int m, int f);

uint64_t start, end;// Global variables to store the CPU clock cycle timestamps (start and end)

int main (void) {
  int i;
  int v[10000] = {}; // Declaration of an array to be sorted(can have any number of elements, now it is size 10000, but the size may increase or decrease depending on the demand)
   //You can paste the numbers in the array manually
  start = __rdtsc();// Starts the timer of how much time(measured in CPU clock ticks) it takes to sort(max measurement time limited to a long int)
  
  mergesort(v, 10000);// Calls the Merge Sort Function giving it its array and size , it says it is size 10000,but the size may increase or decrease depending on the demand

  end = __rdtsc();// Finishes the timer of sorting
  
  for (i = 0; i < 10000; i++) printf("%d ", v[i]);// Loop to print all the elements sorted
  putchar('\n');//breaks line

  printf("CPU clock ticks consumed: %lu\n", (end - start));// Prints all the CPU clock ticks consumed
  
  return 0;
}


void mergesort(int *v, int n) {  // Merge Sort interface function: Memory allocs the auxiliary vector and starts recursion
  int *c = malloc(sizeof(int) * n);// Dynamic allocates a temporary vector 'c' with the same size of the original unsorted array 
  sort(v, c, 0, n - 1);// Starts recursive function of dividing going through initial (0) index to last index (n - 1)
  free(c);// Frees auxiliary vector in memory 
}


void sort(int *v, int *c, int i, int f) {// Recursive function dividing vector  in halves (Divide and Conquer)
  if (i >= f) return;// Basic case: if initial index is greater or equal in the end , the sublist has 1 or 0 elements 

  int m = (i + f) / 2;// Finds the middle point of current interval to make division

  sort(v, c, i, m);// Recursively divides the first half (start to middle)
  sort(v, c, m + 1, f);// Recursively divides the second half (middle to end)

  
  if (v[m] <= v[m + 1]) return;// Optimization: If greatenst element of the first half is smaller of equal to the amaller of the second half,
                              // it means  that this part is perfectly ordered , not need interspersing 
  merge(v, c, i, m, f);// Intersperse the two ordered halves in one sigle ordered part ordenado
}



void merge(int *v, int *c, int i, int m, int f) {// Function interspersing(conbining) two ordered sub-lists back to the original array 
  int z,                      // Index to go through the first half of the auxiliary vector  
      iv = i, ic = m + 1;     // Index to go through the second half of the auxiliary vector

  for (z = i; z <= f; z++) c[z] = v[z];// Copies the elements of the current original vector 'v' to the auxilary vector 'c' 

  z = i;// Restarts 'z' to reposition the ordered elements back to 'v' 

  while (iv <= m && ic <= f) {// Compares the elements of two halves of the auxiliary vector and copying the smaller back to 'v'

    if (c[iv] <= c[ic]) v[z++] = c[iv++];
    else v[z++] = c[ic++];
  }

  while (iv <= m) v[z++] = c[iv++]; // If there are elements left in the firts half, copies all of them back to 'v'

  while (ic <= f) v[z++] = c[ic++]; // If there are elements left in the firts half, copies all of them back to 'v'
}
