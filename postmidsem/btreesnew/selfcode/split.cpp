#include<bits/stdc++.h>
using namespace std;

class btreenode
{
public:

	int * key;
	btreenode ** C;
	int t;
	int n;
	bool leaf;
	btreenode(int tt, bool l);
	btreenode * insertnofull(int k, int & temp);
	btreenode * split(int & temp);
	void traverse(); 
	btreenode *search(int k);
};

class btree
{
public:

	btreenode * root;
	int t;
	btree(int tt);
	void insert(int k);
	void traverse() 
	{ if (root != NULL) root->traverse(); } 

	// function to search a key in this tree 
	btreenode* search(int k) 
	{ return (root == NULL)? NULL : root->search(k); } 
};

btreenode:: btreenode(int tt, bool l)
{
	t=tt;
	leaf=l;
	key= new int [2*t];
	C= new btreenode * [2*t+1];
	for(int i=0;i<2*t+1;i++)
		C[i]=NULL;
	n=0;
}


void btreenode::traverse() 
{ 
	// There are n keys and n+1 children, travers through n keys 
	// and first n children 
	// int i; 
	// for (i = 0; i < n; i++) 
	// { 
	// 	// If this is not leaf, then before printing key[i], 
	// 	// traverse the subtree rooted with child C[i]. 
	// 	if (leaf == false) 
	// 		C[i]->traverse(); 
	// 	cout << " " << key[i]; 
	// } 

	// // Print the subtree rooted with last child 
	// if (leaf == false) 
	// 	C[i]->traverse();

	int i;
	for(i=0;i<n;i++)
		cout<<" "<<key[i];

	cout<<endl;

	if(leaf==false)
	for(int i=0;i<n+1;i++)
		C[i]->traverse();
} 

// Function to search key k in subtree rooted with this node 
btreenode *btreenode::search(int k) 
{ 
	// Find the first key greater than or equal to k 
	int i = 0; 
	while (i < n && k > key[i]) 
		i++; 

	// If the found key is equal to k, return this node 
	if (key[i] == k) 
		return this; 

	// If key is not found here and this is a leaf node 
	if (leaf == true) 
		return NULL; 

	// Go to the appropriate child 
	return C[i]->search(k); 
} 

btreenode * btreenode :: insertnofull(int k, int & temp)
{
	btreenode * z=NULL;
	if(leaf==1)
	{
		int i=n-1;
		while(i>=0 && key[i]>k)
				i--;
			for(int j=n-1;j>i;j--)
			{
				key[j+1]=key[j];
			}

			key[i+1]=k;
			n++;
			if(n==2*t)
			{
				z=split(temp);
				n=t;
			}
		return z;

	}
	int i=n-1;
	btreenode * z2=NULL;
	while(i>=0 && key[i]>k)
				i--;
	z2=C[i+1]->insertnofull(k,temp);

	if(z2!=NULL)
	{
		for(int j=n-1;j>i;j--)
			{
				key[j+1]=key[j];
			}

			key[i+1]=temp;
		for(int j=n-1;j>i;j--)
		{
			C[j+2]=C[j+1];
		}
		C[i+2]=z2;
		n++;
		
		if(n==2*t)
			{
				z=split(temp);
				n=t;
			}
	}
	return z;
}

btreenode * btreenode :: split(int & temp)
{
	btreenode * z= new btreenode(t,leaf);

	for(int j=0;j<t-1;j++)
	{
		z->key[j]=key[t+1+j];
	}

	if(leaf==0)
	{
		for(int j=0;j<t;j++)
			z->C[j]=C[t+1+j];
	}

	temp=key[t];
	n=t;
	z->n=t-1;
	return z;
}

btree:: btree(int tt)
{
	t=tt;
	root=NULL;
}

void btree:: insert(int k)
{
	if(root==NULL)
	{
		root=new btreenode(t,1);
		root->key[0]=k;
		root->n=1;
	}

	else
	{
		int temp=-1;
		btreenode * z=root->insertnofull(k,temp);
		if(z!=NULL)
		{
			
				btreenode * s=new btreenode (t,0);
				s->C[0]=root;
				s->C[1]=z;
				s->n=1;
				s->key[0]=temp;
				root=s;

		}
	}
}


int main()
{
	int tt;
	cin>>tt;
	btree t(tt); 
	int a;
	do
	{
		cin>>a;
		if(a!=-1)
			{
				t.insert(a);
				t.traverse();
			}
	} while(a!=-1);
	// t.insert(10); 
	// t.insert(20); 
	// t.insert(5); 
	// t.insert(6); 
	// t.insert(12); 
	// t.insert(30); 
	// t.insert(7); 
	// t.insert(17); 

	cout << "Traversal of the constucted tree is "; 
	t.traverse(); 

	int k = 6; 
	(t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present"; 

	k = 15; 
	(t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present"; 

	return 0; 
}