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

treenode* search(treenode* root,int d)
{
	if(root==NULL)
		return NULL;
	treenode* temp=root;

	while(temp!=NULL)
	{
		if(temp->data==d)
			return temp;

		if(temp->data>d)
			temp=temp->left;
		else
			temp=temp->right;
	}

	return NULL;
}

treenode* minimum(treenode* root)
{
	if(root==NULL)
		return NULL;
	treenode* y=NULL;
	while(root!=NULL)
		{	
			y=root;
			root=root->left;
		}

	return y;
}

treenode* successor(treenode* temp)
{
	treenode* x=temp;
	if(x->right!=NULL)
	{
		return minimum(x->right);
	}

	treenode* y=x->parent;
	while(y!=NULL)
	{
		if(y->left==x)
			return y;
		x=y;
		y=y->parent;
	}

	return NULL;

}

treenode* deletenode(treenode* root,int d)
{
	treenode* temp=search(root,d);
	if(temp==NULL)
		return NULL;

	if(temp->left==NULL && temp->right==NULL)
	{
		treenode* p=temp->parent;
		if(p==NULL)
		{
			delete temp;
			return NULL;
		}
		if(p->left==temp)
			p->left=NULL;
		else
			p->right=NULL;
		delete temp;

		return root;
	}

	if(temp->left==NULL)
	{
		treenode* p=temp->parent;
		if(p==NULL)
		{
			temp->right->parent=NULL;
			treenode* temp1=temp->right;
			delete temp;
			return temp1;

		}
		if(p->left==temp)
		{
			p->left=temp->right;
			
		}
		else
		{
			p->right=temp->right;
		}
		temp->right->parent=p;

		delete temp;
		return root;
	}

	if(temp->right==NULL)
	{
		treenode* p=temp->parent;
		if(p==NULL)
		{
			temp->left->parent=NULL;
			treenode* temp1=temp->left;
			delete temp;
			return temp1;

		}
		if(p->left==temp)
		{
			p->left=temp->left;
			
		}
		else
		{
			p->right=temp->left;
		}
		temp->left->parent=p;
		
		delete temp;
		return root;
	}

	treenode* helper=successor(temp);
	int help=helper->data;
	treenode* lol=deletenode(root,help);
	temp->data=help;

	return lol;

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

void inorder(treenode* root)
{
	if(root==NULL)
		return;
	inorder(root->left);
	cout<<root->data<<" ";
	inorder(root->right);
}

int main()
{
	treenode* root=takeinput();
	inorder(root);
	cout<<endl<<endl;

	cout<<"enter number of nodes to be deleted: ";
	int l;
	cin>>l;
	for(int i=0;i<l;i++)
	{
		int b;
		cin>>b;
	root=deletenode(root,b);
	inorder(root);
	}

	return 0;	
}