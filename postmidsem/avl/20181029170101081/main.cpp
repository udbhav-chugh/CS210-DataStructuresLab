#include<bits/stdc++.h>
using namespace std;

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


treenode* insert(treenode* root, int d)
{
	if(root==NULL)
	{
		root=createnode(d,NULL);
		return root;
	}

	treenode* x=root;
	treenode* y=NULL;
	while(x!=NULL)
	{
		y=x;
		if(x->data>=d)
			{
				x->lnode++;
				x=x->left;
			}

		else
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

	int mid=(end+start)/2;
	root=insert(root,arr[mid]);

	solve(arr,start,mid-1,root);
	solve(arr,mid+1,end,root);
	return root;

}


void printsequence(treenode* root)
{
	queue<treenode*> q;

	cout<<"Sequence of insertions: ";
	q.push(root);

	while(q.empty()==0)
	{
		treenode* t=q.front();
		q.pop();

		cout<<t->data;

		if(t->left!=NULL)
			q.push(t->left);

		if(t->right!=NULL)
			q.push(t->right);
		
		
		if(q.empty()==0)
			cout<<", ";
	}
}

void printstructure(treenode* root)
{

	cout<<endl<<endl<<"Tree structure: "<<endl;

	queue<treenode *> q;
	q.push(root);

	while(q.empty()==0)
	{
		cout<<endl;
		treenode* t=q.front();
		q.pop();

		cout<<"Node: "<<t->data<<"  Parent: ";
		if(t->parent!=NULL)
			cout<<t->parent->data<<endl;
		else
			cout<<"NULL"<<endl;


		cout<<"Left Child: ";
		if(t->left==NULL)
			cout<<"NULL";
		else
			{
				cout<<t->left->data;
				q.push(t->left);
			}

		cout<<"  Nodes in left subtree: "<<t->lnode;

		cout<<"  Right Child: ";
		if(t->right==NULL)
			cout<<"NULL";
		else
			{
				cout<<t->right->data;
				q.push(t->right);
			}

		cout<<"  Nodes in right subtree: "<<t->rnode<<endl;
	}	
}

int main()
{
	treenode * root=NULL;
	int temp;
	int n=0;
	vector<int> v;
	while(cin>>temp)
	{
		v.push_back(temp);
	}
	n=v.size();
	int * arr=new int[n];

	sort(v.begin(),v.end());

	for(int i=0;i<n;i++)
		arr[i]=v[i];

	root=solve(arr,0,n-1,root);

	printsequence(root);
	printstructure(root);	

	delete [] arr;
	return 0;
}