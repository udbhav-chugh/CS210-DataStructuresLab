#include<iostream> 
using namespace std; 
  
// An AVL tree Node 
struct Node 
{ 
    int key; 
    struct Node *left, *right; 
    int height, count; 
}; 
  
// Function to isnert a key in AVL Tree, if key is already present, 
// then it increments count in key's node. 
struct Node* insert(struct Node* Node, int key); 
  
// This function puts inorder traversal of AVL Tree in arr[] 
void inorder(int arr[], struct Node *root, int *index_ptr); 
  
// An AVL tree based sorting function for sorting an array with 
// duplicates 
void sort(int arr[], int n) 
{ 
  // Create an empty AVL Tree 
  struct Node *root = NULL; 
  
  // Insert all nodes one by one in AVL tree. The insert function 
  // increments count if key is already present 
  for (int i=0; i<n; i++) 
     root = insert(root, arr[i]); 
  
  // Do inorder traversal to put elements back in sorted order 
  int index = 0; 
  inorder(arr, root, &index); 
} 
  
// This function puts inorder traversal of AVL Tree in arr[] 
void inorder(int arr[], struct Node *root, int *index_ptr) 
{ 
    if (root != NULL) 
    { 
        // Recur for left child 
        inorder(arr, root->left, index_ptr); 
  
        // Put all occurrences of root's key in arr[] 
        for (int i=0; i<root->count; i++) 
        { 
           arr[*index_ptr] = root->key; 
           (*index_ptr)++; 
        } 
  
        // Recur for right child 
        inorder(arr, root->right, index_ptr); 
    } 
} 
  
// A utility function to get height of the tree 
int height(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
// Helper function that allocates a new Node 
struct Node* newNode(int key) 
{ 
    struct Node* node = new Node; 
    node->key   = key; 
    node->left   = node->right = NULL; 
    node->height = node->count = 1; 
    return(node); 
} 
  
// A utility function to right rotate subtree rooted 
// with y. 
struct Node *rightRotate(struct Node *y) 
{ 
    struct Node *x = y->left; 
    struct Node *T2 = x->right; 
  
    // Perform rotation 
    x->right = y; 
    y->left = T2; 
  
    // Update heights 
    y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 
  
    // Return new root 
    return x; 
} 
  
// A utility function to left rotate subtree rooted with x 
struct Node *leftRotate(struct Node *x) 
{ 
    struct Node *y = x->right; 
    struct Node *T2 = y->left; 
  
    // Perform rotation 
    y->left = x; 
    x->right = T2; 
  
    //  Update heights 
    x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
  
    // Return new root 
    return y; 
} 
  
// Get Balance factor of Node N 
int getBalance(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
} 
  
// Function to insert a key in AVL Tree, if key is already 
// present, then it increments count in key's node. 
struct Node* insert(struct Node* Node, int key) 
{ 
    /* 1.  Perform the normal BST rotation */
    if (Node == NULL) 
        return (newNode(key)); 
  
    // If key already exists in BST, icnrement count and return 
    if (key == Node->key) 
    { 
        (Node->count)++; 
        return Node; 
    } 
  
     /* Otherwise, recur down the tree */
    if (key < Node->key) 
        Node->left  = insert(Node->left, key); 
    else
        Node->right = insert(Node->right, key); 
  
    /* 2. Update height of this ancestor Node */
    Node->height = max(height(Node->left), height(Node->right)) + 1; 
  
    /* 3. Get the balance factor of this ancestor Node to 
       check whether this Node became unbalanced */
    int balance = getBalance(Node); 
  
    // If this Node becomes unbalanced, then there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && key < Node->left->key) 
        return rightRotate(Node); 
  
    // Right Right Case 
    if (balance < -1 && key > Node->right->key) 
        return leftRotate(Node); 
  
    // Left Right Case 
    if (balance > 1 && key > Node->left->key) 
    { 
        Node->left =  leftRotate(Node->left); 
        return rightRotate(Node); 
    } 
  
    // Right Left Case 
    if (balance < -1 && key < Node->right->key) 
    { 
        Node->right = rightRotate(Node->right); 
        return leftRotate(Node); 
    } 
  
    /* return the (unchanged) Node pointer */
    return Node; 
} 
  
// A utility function to print an array 
void printArr(int arr[], int n) 
{ 
    for (int i=0; i<n; i++) 
       cout << arr[i] << ", "; 
    cout << endl; 
} 
  
/* Driver program to test above function*/
int main() 
{ 
  int arr[] = {100, 12, 100, 1, 1, 12, 100, 1, 12, 100, 1, 1}; 
  int n = sizeof(arr)/sizeof(arr[0]); 
  
  cout << "Input array is\n"; 
  printArr(arr, n); 
  
  sort(arr, n); 
  
  cout << "Sorted array is\n"; 
  printArr(arr, n); 
} 