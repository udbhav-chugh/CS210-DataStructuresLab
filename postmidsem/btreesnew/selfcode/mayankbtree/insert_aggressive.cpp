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

int main() 
{ 
	BTree t(2); // A B-Tree with minium degree 3 
	srand(time(0));
	// t.insert(10); 
	// t.insert(20); 
	// t.insert(5); 
	// t.insert(6); 
	// t.insert(12); 
	// t.insert(30); 
	// t.insert(7); 
	// t.insert(17); 
	int done[10001] = {0}, num;
	cout << "Inserted numbers:  "; 
	for (int i=1; i<=20; i++){
		num = rand()%10 + 1;
		if (done[num] == 0){ 
			t.insert(num);
			done[num]=1;
			// cout<<"Inserted number: "<<num<<" ";
			// t.level();
		}	
	} 

	cout << "\nTraversal of the constucted tree is "; 
	// traverse(); 
	t.level(); 

	int k = 6; 
	(t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present"; 

	k = 15; 
	(t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present"; 

	return 0; 
} 
