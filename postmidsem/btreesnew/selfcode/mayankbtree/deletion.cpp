#include<bits/stdc++.h>

using namespace std;

class Node{
public:
	int t;
	int *keys;
	Node **C;
	int n;
	bool leaf;
	Node(int _t, bool leaf);
	void traverse();
	void level();
	Node* search(int k);
	void insertNotFull(int k);
	void split(int i, Node* chd);

	int findKey(int k); 

	// A utility function to insert a new key in the subtree rooted with 
	// this node. The assumption is, the node must be non-full when this 
	// function is called 

	// A utility function to split the child y of this node. i is index 
	// of y in child array C[]. The Child y must be full when this 
	// function is called 

	// A wrapper function to remove the key k in subtree rooted with 
	// this node. 
	void remove(int k); 

	// A function to remove the key present in idx-th position in 
	// this node which is a leaf 
	void removeFromLeaf(int idx); 

	// A function to remove the key present in idx-th position in 
	// this node which is a non-leaf node 
	void removeFromNonLeaf(int idx); 

	// A function to get the predecessor of the key- where the key 
	// is present in the idx-th position in the node 
	int getPred(int idx); 

	// A function to get the successor of the key- where the key 
	// is present in the idx-th position in the node 
	int getSucc(int idx); 

	// A function to fill up the child node present in the idx-th 
	// position in the C[] array if that child has less than t-1 keys 
	void fill(int idx); 

	// A function to borrow a key from the C[idx-1]-th node and place 
	// it in C[idx]th node 
	void borrowFromPrev(int idx); 

	// A function to borrow a key from the C[idx+1]-th node and place it 
	// in C[idx]th node 
	void borrowFromNext(int idx); 

	// A function to merge idx-th child of the node with (idx+1)th child of 
	// the node 
	void merge(int idx); 

};

class BTree{
public:
	int t;
	Node* root;
	BTree(int _t);
	void insert(int k);
	void traverse(){ 
		if (root != NULL) root->traverse(); 
	}
	void level(){ 
		if (root != NULL) root->level(); 
	} 

	Node* search(int k){ 
		return (root == NULL)? NULL : root->search(k); 
	}
	void remove(int k);  
};

Node::Node(int _t, bool lef){
	t=_t;
	keys = new int[2*t-1];
	leaf = lef;
	C = new Node*[2*t];
	n = 0;
}

BTree::BTree (int _t){
	t = _t;
	root = NULL;
}


int Node::findKey(int k) 
{ 
	int idx=0; 
	while (idx<n && keys[idx] < k) 
		++idx; 
	return idx; 
} 

// A function to remove the key k from the sub-tree rooted with this node 
void Node::remove(int k) 
{ 
	int idx = findKey(k); 

	// The key to be removed is present in this node 
	if (idx < n && keys[idx] == k) 
	{ 

		// If the node is a leaf node - removeFromLeaf is called 
		// Otherwise, removeFromNonLeaf function is called 
		if (leaf) 
			removeFromLeaf(idx); 
		else
			removeFromNonLeaf(idx); 
	} 
	else
	{ 

		// If this node is a leaf node, then the key is not present in tree 
		if (leaf) 
		{ 
			cout << "The key "<< k <<" is does not exist in the tree\n"; 
			return; 
		} 

		// The key to be removed is present in the sub-tree rooted with this node 
		// The flag indicates whether the key is present in the sub-tree rooted 
		// with the last child of this node 
		bool flag = ( (idx==n)? true : false ); 

		// If the child where the key is supposed to exist has less that t keys, 
		// we fill that child 
		if (C[idx]->n < t) 
			fill(idx); 

		// If the last child has been merged, it must have merged with the previous 
		// child and so we recurse on the (idx-1)th child. Else, we recurse on the 
		// (idx)th child which now has atleast t keys 
		if (flag && idx > n) 
			C[idx-1]->remove(k); 
		else
			C[idx]->remove(k); 
	} 
	return; 
} 

// A function to remove the idx-th key from this node - which is a leaf node 
void Node::removeFromLeaf (int idx) 
{ 

	// Move all the keys after the idx-th pos one place backward 
	for (int i=idx+1; i<n; ++i) 
		keys[i-1] = keys[i]; 

	// Reduce the count of keys 
	n--; 

	return; 
} 

// A function to remove the idx-th key from this node - which is a non-leaf node 
void Node::removeFromNonLeaf(int idx) 
{ 

	int k = keys[idx]; 

	// If the child that precedes k (C[idx]) has atleast t keys, 
	// find the predecessor 'pred' of k in the subtree rooted at 
	// C[idx]. Replace k by pred. Recursively delete pred 
	// in C[idx] 
	if (C[idx]->n >= t) 
	{ 
		int pred = getPred(idx); 
		keys[idx] = pred; 
		C[idx]->remove(pred); 
	} 

	// If the child C[idx] has less that t keys, examine C[idx+1]. 
	// If C[idx+1] has atleast t keys, find the successor 'succ' of k in 
	// the subtree rooted at C[idx+1] 
	// Replace k by succ 
	// Recursively delete succ in C[idx+1] 
	else if (C[idx+1]->n >= t) 
	{ 
		int succ = getSucc(idx); 
		keys[idx] = succ; 
		C[idx+1]->remove(succ); 
	} 

	// If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1] 
	// into C[idx] 
	// Now C[idx] contains 2t-1 keys 
	// Free C[idx+1] and recursively delete k from C[idx] 
	else
	{ 
		merge(idx); 
		C[idx]->remove(k); 
	} 
	return; 
} 

// A function to get predecessor of keys[idx] 
int Node::getPred(int idx) 
{ 
	// Keep moving to the right most node until we reach a leaf 
	Node *cur=C[idx]; 
	while (!cur->leaf) 
		cur = cur->C[cur->n]; 

	// Return the last key of the leaf 
	return cur->keys[cur->n-1]; 
} 

int Node::getSucc(int idx) 
{ 

	// Keep moving the left most node starting from C[idx+1] until we reach a leaf 
	Node *cur = C[idx+1]; 
	while (!cur->leaf) 
		cur = cur->C[0]; 

	// Return the first key of the leaf 
	return cur->keys[0]; 
} 

// A function to fill child C[idx] which has less than t-1 keys 
void Node::fill(int idx) 
{ 

	// If the previous child(C[idx-1]) has more than t-1 keys, borrow a key 
	// from that child 
	if (idx!=0 && C[idx-1]->n>=t) 
		borrowFromPrev(idx); 

	// If the next child(C[idx+1]) has more than t-1 keys, borrow a key 
	// from that child 
	else if (idx!=n && C[idx+1]->n>=t) 
		borrowFromNext(idx); 

	// Merge C[idx] with its sibling 
	// If C[idx] is the last child, merge it with with its previous sibling 
	// Otherwise merge it with its next sibling 
	else
	{ 
		if (idx != n) 
			merge(idx); 
		else
			merge(idx-1); 
	} 
	return; 
} 

// A function to borrow a key from C[idx-1] and insert it 
// into C[idx] 
void Node::borrowFromPrev(int idx) 
{ 

	Node *child=C[idx]; 
	Node *sibling=C[idx-1]; 

	// The last key from C[idx-1] goes up to the parent and key[idx-1] 
	// from parent is inserted as the first key in C[idx]. Thus, the loses 
	// sibling one key and child gains one key 

	// Moving all key in C[idx] one step ahead 
	for (int i=child->n-1; i>=0; --i) 
		child->keys[i+1] = child->keys[i]; 

	// If C[idx] is not a leaf, move all its child pointers one step ahead 
	if (!child->leaf) 
	{ 
		for(int i=child->n; i>=0; --i) 
			child->C[i+1] = child->C[i]; 
	} 

	// Setting child's first key equal to keys[idx-1] from the current node 
	child->keys[0] = keys[idx-1]; 

	// Moving sibling's last child as C[idx]'s first child 
	if(!child->leaf) 
		child->C[0] = sibling->C[sibling->n]; 

	// Moving the key from the sibling to the parent 
	// This reduces the number of keys in the sibling 
	keys[idx-1] = sibling->keys[sibling->n-1]; 

	child->n += 1; 
	sibling->n -= 1; 

	return; 
} 

// A function to borrow a key from the C[idx+1] and place 
// it in C[idx] 
void Node::borrowFromNext(int idx) 
{ 

	Node *child=C[idx]; 
	Node *sibling=C[idx+1]; 

	// keys[idx] is inserted as the last key in C[idx] 
	child->keys[(child->n)] = keys[idx]; 

	// Sibling's first child is inserted as the last child 
	// into C[idx] 
	if (!(child->leaf)) 
		child->C[(child->n)+1] = sibling->C[0]; 

	//The first key from sibling is inserted into keys[idx] 
	keys[idx] = sibling->keys[0]; 

	// Moving all keys in sibling one step behind 
	for (int i=1; i<sibling->n; ++i) 
		sibling->keys[i-1] = sibling->keys[i]; 

	// Moving the child pointers one step behind 
	if (!sibling->leaf) 
	{ 
		for(int i=1; i<=sibling->n; ++i) 
			sibling->C[i-1] = sibling->C[i]; 
	} 

	// Increasing and decreasing the key count of C[idx] and C[idx+1] 
	// respectively 
	child->n += 1; 
	sibling->n -= 1; 

	return; 
} 

// A function to merge C[idx] with C[idx+1] 
// C[idx+1] is freed after merging 
void Node::merge(int idx) 
{ 
	Node *child = C[idx]; 
	Node *sibling = C[idx+1]; 

	// Pulling a key from the current node and inserting it into (t-1)th 
	// position of C[idx] 
	child->keys[t-1] = keys[idx]; 

	// Copying the keys from C[idx+1] to C[idx] at the end 
	for (int i=0; i<sibling->n; ++i) 
		child->keys[i+t] = sibling->keys[i]; 

	// Copying the child pointers from C[idx+1] to C[idx] 
	if (!child->leaf) 
	{ 
		for(int i=0; i<=sibling->n; ++i) 
			child->C[i+t] = sibling->C[i]; 
	} 

	// Moving all keys after idx in the current node one step before - 
	// to fill the gap created by moving keys[idx] to C[idx] 
	for (int i=idx+1; i<n; ++i) 
		keys[i-1] = keys[i]; 

	// Moving the child pointers after (idx+1) in the current node one 
	// step before 
	for (int i=idx+2; i<=n; ++i) 
		C[i-1] = C[i]; 

	// Updating the key count of child and the current node 
	child->n += sibling->n+1; 
	n--; 

	// Freeing the memory occupied by sibling 
	delete(sibling); 
	return; 
} 


void Node::split(int i, Node* c1){
	Node* c2 = new Node(t,c1->leaf);
	for (int j=0; j<t-1; j++){
		c2->keys[j] = c1->keys[j+t];
	}
	if (c1->leaf == false){
		for (int j=0; j<t; j++){
			c2->C[j] = c1->C[j+t];
		}
	}
	c2->n = t-1;
	c1->n = t-1;
	
	for (int j=n-1; j>=i; j--)
		keys[j+1] = keys[j];
	keys[i] = c1->keys[t-1];
	
	for (int j=n; j>i; j--)
		C[j+1] = C[j];
	C[i+1] = c2;
	n = n+1;
}

void Node::insertNotFull (int k){
	if (leaf == true){
		int i=n-1;
		while (i>=0 && keys[i]>k){
			keys[i+1] = keys[i];
			i--;
		}
		keys[i+1] = k;
		n=n+1;
	}
	else{
		int i=n-1;
		while (i>=0 && keys[i]>k)
			i--;
		if (C[i+1]->n == 2*t-1){
			split (i+1, C[i+1]);
			if (keys[i+1] < k)
				i++;
		}
		C[i+1]->insertNotFull(k);
	}
}

void BTree::insert(int k){
	if (root == NULL){
		root = new Node(t,true);
		root->keys[0] = k;
		root->n = 1;
	}
	else{
		if (root->n == 2*t-1){
			Node* sproot = new Node(t, false);
			sproot->C[0] = root;
			sproot->split (0, root);

			int i=0;
			if (k > sproot->keys[0])
				i++;
			sproot->C[i]->insertNotFull(k);
			root = sproot;
		}
		else
			root->insertNotFull(k);
	}
}

void Node::traverse() 
{ 
	int i; 
	for (i = 0; i < n; i++) 
	{ 
		if (leaf == false) 
			C[i]->traverse(); 
		cout << " " << keys[i]; 
	} 

	if (leaf == false) 
		C[i]->traverse(); 
} 

void Node::level() 
{ 
	int i; 
	for (i = 0; i < n; i++)  
		cout <<" "<< keys[i]; 
	 
	cout<<"\n";
	if (leaf == false){
		for (i = 0; i < n; i++)
			C[i]->level(); 

		C[i]->level(); 
	}
} 

Node* Node::search(int k){
	int i=0;
	while (i < n && k > keys[i]) 
		i++; 
	if (keys[i] == k) 
		return this; 
	if (leaf == true) 
		return NULL; 
	return C[i]->search(k); 
}

void BTree::remove(int k) 
{ 
	if (!root) 
	{ 
		cout << "The tree is empty\n"; 
		return; 
	} 

	// Call the remove function for root 
	root->remove(k); 

	// If the root node has 0 keys, make its first child as the new root 
	// if it has a child, otherwise set root as NULL 
	if (root->n==0) 
	{ 
		Node *tmp = root; 
		if (root->leaf) 
			root = NULL; 
		else
			root = root->C[0]; 

		// Free the old root 
		delete tmp; 
	} 
	return; 
} 


int main() 
{ 
	BTree t(2); // A B-Tree with minium degree 3 
	// srand(time(0));
	// // t.insert(10); 
	// // t.insert(20); 
	// // t.insert(5); 
	// // t.insert(6); 
	// // t.insert(12); 
	// // t.insert(30); 
	// // t.insert(7); 
	// // t.insert(17); 
	// int done[10001] = {0}, num;
	// cout << "Inserted numbers:  "; 
	// for (int i=1; i<=20; i++){
	// 	num = rand()%10 + 1;
	// 	if (done[num] == 0){ 
	// 		t.insert(num);
	// 		done[num]=1;
	// 		// cout<<"Inserted number: "<<num<<" ";
	// 		// t.level();
	// 	}	
	// } 

	// cout << "\nTraversal of the constucted tree is "; 
	// // traverse(); 
	// t.level(); 

	// int k = 6; 
	// (t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present"; 

	// k = 15; 
	// (t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present"; 


	t.insert(1); 
	t.insert(3); 
	t.insert(7); 
	t.insert(10); 
	t.insert(11); 
	t.insert(13); 
	t.insert(14); 
	t.insert(15); 
	t.insert(18); 
	t.insert(16); 
	t.insert(19); 
	t.insert(24); 
	t.insert(25); 
	t.insert(26); 
	t.insert(21); 
	t.insert(4); 
	t.insert(5); 
	t.insert(20); 
	t.insert(22); 
	t.insert(2); 
	t.insert(17); 
	t.insert(12); 
	t.insert(6); 

	cout << "Traversal of tree constructed is\n"; 
	t.traverse(); 
	cout << endl; 

	t.remove(6); 
	cout << "Traversal of tree after removing 6\n"; 
	t.traverse(); 
	cout << endl; 

	t.remove(13); 
	cout << "Traversal of tree after removing 13\n"; 
	t.traverse(); 
	cout << endl; 

	t.remove(7); 
	cout << "Traversal of tree after removing 7\n"; 
	t.traverse(); 
	cout << endl; 

	t.remove(4); 
	cout << "Traversal of tree after removing 4\n"; 
	t.traverse(); 
	cout << endl; 

	t.remove(2); 
	cout << "Traversal of tree after removing 2\n"; 
	t.traverse(); 
	cout << endl; 

	t.remove(16); 
	cout << "Traversal of tree after removing 16\n"; 
	t.traverse(); 
	cout << endl; 




	return 0; 
} 
