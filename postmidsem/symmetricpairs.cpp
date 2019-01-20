// // Given an array of pairs, find all symmetric pairs in it
// An Efficient Solution is to use Hashing.
 // First element of pair is used as key and second element is used as value. 
 // The idea is traverse all pairs one by one. 
 // For every pair, check if its second element is in hash table. 
 // If yes, then compare the first element with value of matched entry of hash table. 
 // If the value and the first element match, then we found symmetric pairs. 
 // Else, insert first element as key and second element as value



#include<bits/stdc++.h> 
using namespace std; 
  
// A C++ program to find all symmetric pairs in a given array of pairs 
// Print all pairs that have a symmetric counterpart 
void findSymPairs(int arr[][2], int row) 
{ 
    // Creates an empty hashMap hM 
    unordered_map<int, int> hM; 
  
    // Traverse through the given array 
    for (int i = 0; i < row; i++) 
    { 
        // First and second elements of current pair 
        int first = arr[i][0]; 
        int sec   = arr[i][1]; 
  
        // If found and value in hash matches with first 
        // element of this pair, we found symmetry 
        if (hM.find(sec) != hM.end() && hM[sec] == first) 
            cout << "(" << sec << ", " << first << ")" <<endl; 
  
        else  // Else put sec element of this pair in hash 
            hM[first] = sec; 
    } 
} 
  
// Drive method 
int main() 
{ 
    int arr[5][2]; 
    arr[0][0] = 11; arr[0][1] = 20; 
    arr[1][0] = 30; arr[1][1] = 40; 
    arr[2][0] = 5;  arr[2][1] = 10; 
    arr[3][0] = 40;  arr[3][1] = 30; 
    arr[4][0] = 10;  arr[4][1] = 5; 
    findSymPairs(arr, 5); 
} 