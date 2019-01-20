#include<iostream>
using namespace std;

struct treenode
{
	int data;
	treenode* left;
	treenode* right;
	bool thread;
};

treenode* createnode(int d)
{
	treenode* temp=new treenode;
	temp->data=d;
	temp->left=NULL;
	temp->right=NULL;
	temp->thread=0;
	return temp;
}

treenode* find(treenode* root, int parent)
{
	if(root==NULL)
		return NULL;
	if(root->data==parent)
		return root;
	treenode* temp=find(root->left,parent);
	if(temp!=NULL)
		return temp;
	else if(root->thread==0)
		return find(root->right,parent);
	return NULL;
}

void setleft(treenode* p, treenode* c)
{
	p->left=c;
	c->thread=1;
	c->right=p;
}

void setright(treenode* p,treenode* c)
{
	c->right=p->right;
	p->right=c;
	p->thread=0;
	c->thread=1;

}

treenode* leftmost(treenode* temp)
{
	while(temp->left!=NULL)
	{
		temp=temp->left;
	}
	return temp;
}

int main()
{
	int d,n;
	cin>>n;
	cout<<"Enter root: ";
	cin>>d;
	treenode * root=createnode(d);

	for(int i=0;i<n-1;i++)
	{
		int parent,child;
		char ch;
		cout<<"enter parent, child, left/right: ";
		cin>>parent>>child>>ch;

		treenode* p=find(root,parent);
		treenode* c=createnode(child);
		if(ch=='L')
			setleft(p,c);
		else
			setright(p,c);

	}

	/*treenode* temp=root;
	int count=0;
	while(temp!=NULL)
	{
		if(count==0)
		temp=leftmost(temp);

		cout<<temp->data<<" ";
		if(temp->thread==1)
		{
			temp=temp->right;
			count=1;
		}
		else
		{
			temp=temp->right;
			count=0;
		}
	}*/

	treenode* temp=root;
	while(temp!=NULL)
	{
		while(temp->left!=NULL)
		{
			cout<<temp->data<<" ";
			temp=temp->left;
		}
		cout<<temp->data<<" ";
		while(temp!=NULL && temp->thread==1)
				temp=temp->right;
			if(temp!=NULL)
		temp=temp->right;
	}
	return 0;
}

