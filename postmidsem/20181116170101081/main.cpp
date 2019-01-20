#include<bits/stdc++.h>
using namespace std;

//class for node of tree
class treenode
{
public:

	int data;
	treenode* left;
	treenode* right;
	treenode* parent;
	int lnode;
	int rnode;
};

//function to initialise tree node
treenode* createnode(int d,treenode* p)
{
	treenode* temp=new treenode;
	temp->data=d;
	temp->left=NULL;
	temp->right=NULL;
	temp->parent=p;
	temp->lnode=0;
	temp->rnode=0;
	return temp;
}


//function to insert value in treenode
treenode* insert(treenode* root, int d)
{
	if(root==NULL)
	{
		root=createnode(d,NULL); //initialise new node
		return root;
	}

	treenode* x=root;
	treenode* y=NULL;
	while(x!=NULL) //search correct position of node to be inserted
	{
		y=x;
		if(x->data>=d) //if data to be inserted smaller move to left
			{
				x->lnode++;
				x=x->left;
			}

		else	//if data to be inserted bigger move to right
			{
				x->rnode++;
				x=x->right;
			}
	}

	if(y->data>=d)
		y->left=createnode(d,y);
	else
		y->right=createnode(d,y);

	return root;
}

treenode* solve(int * arr, int start, int end, treenode* root)
{
	if(start>end)
		return root;

	int mid=(end+start+1)/2; 
	root=insert(root,arr[mid]); //keep on inserting middle element of sorted array in the tree

	solve(arr,start,mid-1,root); //recursive calls to left and right
	solve(arr,mid+1,end,root);
	return root;

}


void printsequence(treenode * root)
{
	queue<treenode *> q; //queue to maintain level order traversal

	cout<<"Sequence of insertions: ";
	q.push(root);

	while(q.empty()==0)
	{
		vector< treenode * > vec ; //vectoer stores nodes of a particular level
		while(q.empty()==0)
		{
			vec.push_back(q.front());
			cout<<q.front()->data<<" ";
			q.pop();
		}

		for(int i=0;i<vec.size();i++)
		{
			if(vec[i]->left!=NULL)
				q.push(vec[i]->left); //push all left children first
		}

		for(int i=0;i<vec.size();i++)
		{
			if(vec[i]->right!=NULL)
				q.push(vec[i]->right); //then push all right children
		}

	}
	cout<<endl;
}


int main()
{
	treenode * root=NULL; //initialise empty tree
	int temp;
	int n=0;
	vector<int> v;
	//taking input
	while(cin>>temp)
	{
		v.push_back(temp);
	}
	n=v.size();
	int * arr=new int[n];

	sort(v.begin(),v.end()); //sort vector of input

	for(int i=0;i<n;i++)
		arr[i]=v[i];

	root=solve(arr,0,n-1,root);

	printsequence(root);	//call to print the required sequence to build the tree

	delete [] arr; //delete array
	return 0;
}