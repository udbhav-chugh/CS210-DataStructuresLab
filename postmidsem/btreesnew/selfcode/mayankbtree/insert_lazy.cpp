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
	Node* insertNotFull(int k, int &nkey, Node* par, int i);
	Node* split(int &nkey);
	bool redistribute (Node* par, int i);
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
		Node* temp = root->insertNotFull(k, nkey, NULL, 0);
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

bool Node::redistribute(Node* par, int i){
	if (par!=NULL){
		
		int lsize = INT_MAX, rsize=INT_MAX;
		if (i>0 && par->C[i-1]->n < 2*t-1)
			lsize = par->C[i-1]->n;
		if (i<(par->n) && par->C[i+1]->n < 2*t-1)
			rsize = par->C[i+1]->n;
		if (lsize == INT_MAX && rsize == INT_MAX)
			return 0;

		if (min(lsize,rsize)==lsize){
			par->C[i-1]->keys[lsize] = par->keys[i-1];
			par->keys[i-1] = keys[0];
			for (int j=0; j<n-1; j++)
				keys[j] = keys[j+1];
			if (leaf==false){
				par->C[i-1]->C[lsize+1] = C[0];
				for (int j=0; j<n; j++)
					C[j] = C[j+1];
			}
			n--;
			(par->C[i-1]->n)++;
			return 1;
		}
		else{
			for (int j=rsize-1; j>=0; j--)
				par->C[i+1]->keys[j+1] = par->C[i+1]->keys[j];
			par->C[i+1]->keys[0] = par->keys[i];
			par->keys[i] = keys[n-1];
			if (leaf==false){
				for (int j=rsize; j>=0; j--)
					par->C[i+1]->C[j+1] = par->C[i+1]->C[j];
				par->C[i+1]->C[0] = C[n];
			}
			n--;
			(par->C[i+1]->n)++;
			return 1;
		}
	}
	return 0;
}

Node* Node::insertNotFull(int k, int &nkey, Node* par, int ii){
	Node* temp = NULL;
	int i=n-1;
	if (leaf==1){
		while (i>=0 && keys[i]>k){
			keys[i+1] = keys[i];
			i--;
		}
		keys[i+1] = k;
		n++;
		if (n==2*t){
			if (redistribute (par, ii))
				return temp;

			temp = split (nkey);
			n = t;
		}
		return temp;
	}

	while (i>=0 && keys[i]>k){
		i--;
	}
	Node* temp2 = NULL;
	temp2 = C[i+1]->insertNotFull (k,nkey,this,i+1);
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
			if (redistribute (par, ii))
				return temp;
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
		num = rand()%20 + 1;
		if (done[num] == 0){ 
			t.insert(num);
			done[num]=1;
			cout<<num<<" ";
		}	
	}
	cout << "\nTraversal of the constructed tree is "; 
	// t.traverse(); 
	t.level(); 

	int k = 6; 
	(t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present"; 

	k = 15; 
	(t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present"; 
	cout<<endl;
	return 0; 
} 
