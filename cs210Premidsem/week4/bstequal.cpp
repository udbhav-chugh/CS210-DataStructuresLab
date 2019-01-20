#include<iostream>
using namespace std;

struct treenode
{
	int data;
	treenode* left;
	treenode* right;
	treenode* parent;
};

treenode* createnode(int d,treenode* p)
{
	treenode* temp=new treenode;
	temp->data=d;
	temp->left=NULL;
	temp->right=NULL;
	temp->parent=p;
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
			x=x->left;
		else
			x=x->right;
		
	}

	if(y->data>=d)
		y->left=createnode(d,y);
	else
		y->right=createnode(d,y);

	return root;

}

treenode* takeinput()
{
	int n;
	cin>>n;
	int d;
	treenode* root=NULL;
	for(int i=0;i<n;i++)
	{
		cin>>d;
		root=insert(root,d);
	}
	return root;
}

bool compare(treenode* root1,treenode* root2)
{
	if(root1==NULL && root2==NULL)
		return 1;
	if(root1==NULL || root2==NULL)
		return 0;

	bool a=compare(root1->left,root2->left);
	if(a==0)
		return a;
	bool b=compare(root1->right,root2->right);
	return b;
}


int main()
{
	treenode* root1=NULL;
	treenode* root2=NULL;
	cout<<"First: "<<endl;
	root1=takeinput();
	cout<<endl<<"Second: "<<endl;
	root2=takeinput();
	if(compare(root1,root2))
		cout<<"equal"<<endl;
	else
		cout<<"not equal"<<endl;
	return 0;
}