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
	Node* search(int k);
	Node* insertNotFull(int k, int &nkey);
	Node* split(int &nkey);
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

	Node* search(int k){ 
		return (root == NULL)? NULL : root->search(k); 
	} 
};

Node::Node(int _t, bool lef){
	t=_t;
	keys = new int[2*t];
	leaf = lef;
	C = new Node*[2*t+1];
	n = 0;
}

BTree::BTree (int _t){
	t = _t;
	root = NULL;
}

void BTree::insert(int k){
	if (root == NULL){
		root = new Node(t,true);
		root->keys[0] = k;
		root->n = 1;
	}
	else{
		int nkey = -1;
		Node* temp = root->insertNotFull(k, nkey);
		if (temp!=NULL){
			// int nkey = -1;
			Node* sproot = new Node(t, false);
			sproot->C[0] = root;
			// Node* temp = root->split(nkey);
			root->n = t;
			sproot->C[1] = temp;
			sproot->keys[0] = nkey;
			sproot->n=1;
			root = sproot;
		}
	}
}

Node* Node::insertNotFull(int k, int &nkey){
	Node* temp = NULL;
	int i=n-1;
	if (leaf==1){
		while (i>=0 && keys[i]>k){
			keys[i+1] = keys[i];
			i--;
		}
		keys[i+1] = k;
		n++;
		// 	cout<<n;
		if (n==2*t){
			temp = split (nkey);
			n = t;
		}
		// if (k==17)
		// 	cout<<nkey;
		return temp;
	}

	while (i>=0 && keys[i]>k){
		i--;
	}
	Node* temp2 = NULL;
	temp2 = C[i+1]->insertNotFull (k,nkey);
	if (temp2!=NULL){
		int j=n-1;
		for (; j>i; j--)
			keys[j+1] = keys[j];
		keys[j+1] = nkey;
		for (j=n; j>i+1; j--)
			C[j+1] = C[j];
		C[j+1] = temp2;
		n++;
		if (n==2*t){
			temp = split (nkey);
			n = t;
		}
	}
	return temp;
}

Node* Node::split(int &nkey){
	Node* c2 = new Node(t,leaf);
	for (int j=0; j<t-1; j++){
		c2->keys[j] = keys[j+t+1];
	}
	if (leaf == false){
		for (int j=0; j<t; j++){
			c2->C[j] = C[j+t+1];
		}
	}
	c2->n = t-1;
	n=t;
	
	nkey = keys[t];
	return c2;
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
	t.insert(10); 
	t.insert(20); 
	t.insert(5); 
	t.insert(6); 
	t.insert(12); 
	t.insert(30); 
	t.insert(7); 
	t.insert(17); 

	cout << "Traversal of the constucted tree is "; 
	t.traverse(); 

	int k = 6; 
	(t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present"; 

	k = 15; 
	(t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present"; 

	return 0; 
} 
