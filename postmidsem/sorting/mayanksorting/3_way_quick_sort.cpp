// C++ program for 3-way quick sort 
#include <bits/stdc++.h> 
using namespace std; 
  
/* This function partitions a[] in three parts 
   a) a[l..i] contains all elements smaller than pivot 
   b) a[i+1..j-1] contains all occurrences of pivot 
   c) a[j..r] contains all elements greater than pivot */
void partition(int a[], int l, int r, int &i, int &j) 
{ 
    i = l, j = r+1; 
    int p = l, q = r+1; 
    int v = a[l]; 
  
    while (true) 
    { 
        // From left, find the first element greater than 
        // or equal to v. This loop will definitely terminate 
        // as v is last element 
        while (a[++i] < v)
            if (i==r)
                break;
  
        // From right, find the first element smaller than or 
        // equal to v 
        while (v < a[--j]);
            // if (j == l) 
            //     break; 
  
        // If i and j cross, then we are done 
        if (i >= j) break; 
  
        // Swap, so that smaller goes on left greater goes on right 
        swap(a[i], a[j]); 
  
        // Move all same left occurrence of pivot to beginning of 
        // array and keep count using p 
        if (a[i] == v) 
        { 
            p++; 
            swap(a[p], a[i]); 
        } 
  
        // Move all same right occurrence of pivot to end of array 
        // and keep count using q 
        if (a[j] == v) 
        { 
            q--; 
            swap(a[j], a[q]); 
        } 
    } 
  
    // Move pivot element to its correct index 
    swap(a[i], a[l]); 
  
    // Move all left same occurrences from beginning 
    // to adjacent to arr[i] 
    j = i-1; 
    for (int k = l+1; k < p; k++, j--) 
        swap(a[k], a[j]); 
  
    // Move all right same occurrences from end 
    // to adjacent to arr[i] 
    i = i+1; 
    for (int k = r; k > q; k--, i++) 
        swap(a[i], a[k]); 
} 
  
// 3-way partition based quick sort 
void quicksort(int a[], int l, int r) 
{ 
    if (r <= l) return; 
  
    int i, j; 
  
    // Note that i and j are passed as reference 
    partition(a, l, r, i, j); 
  
    // Recur 
    quicksort(a, l, j); 
    quicksort(a, i, r); 
} 
  
// A utility function to print an array 
void printarr(int a[], int n) 
{ 
    for (int i = 0; i < n; ++i) 
        printf("%d  ", a[i]); 
    printf("\n"); 
} 
  
// Driver program 
int main() 
{ 
    int a[] = {7, 2, 5, 2, 9, 5, 3, 2, 1, 1, 4, 2, 6, 6, 8}; 
    int size = sizeof(a) / sizeof(int); 
    printarr(a, size); 
    quicksort(a, 0, size - 1); 
    printarr(a, size); 
    return 0; 
} 