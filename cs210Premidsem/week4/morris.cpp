#include<iostream>
using namespace std;

struct treenode
{
	int data;
	treenode* left;
	treenode* right;
};

treenode* createnode(int d)
{
	treenode* temp=new treenode;
	temp->data=d;
	temp->left=NULL;
	temp->right=NULL;
	return temp;
}

treenode* find(treenode* root, int parent)
{
	if(root==NULL)
		return NULL;

	if(root->data==parent)
		return root;

	treenode* temp1=find(root->left,parent);
	if(temp1!=NULL)
		return temp1;

	return find(root->right,parent);

}

treenode* takeinput()
{
	int n;
	cin>>n;
	int child,parent;
	char ch;
	cin>>child>>parent>>ch;
	treenode* root=createnode(child);

	for(int i=1;i<n;i++)
	{
		cin>>child>>parent>>ch;
		treenode* temp=find(root,parent);
		if(ch=='L')
		{
			temp->left=createnode(child);
		}
		else
		{
			temp->right=createnode(child);
		}
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


void morrisinorder(treenode* root)
{
	if(root==NULL)
		return;

	treenode * p=root;
	while(p!=NULL)
	{
		if(p->left==NULL)
		{
			cout<<p->data<<" ";
			p=p->right;
		}
		else
		{
			treenode* temp=p->left;
			while(temp->right!=NULL && temp->right!=p)
			{
				temp=temp->right;
			}
			if(temp->right==NULL)
			{
				temp->right=p;
				p=p->left;
			}
			else
			{
				cout<<p->data<<" ";
				p=p->right;
				temp->right=NULL;
			}
		}
	}
}

void preorder(treenode* root)
{
	if(root==NULL)
		return;
	cout<<root->data<<" ";
	preorder(root->left);
	preorder(root->right);

}

void morrispreorder(treenode* root)
{
	if(root==NULL)
		return;

	treenode*p=root;

	while(p!=NULL)
	{
		
		if(p->left==NULL)
		{
			cout<<p->data<<" ";
			p=p->right;
		}
		else
		{
			treenode* temp=p->left;
			while(temp->right!=NULL && temp->right!=p)
			{
				temp=temp->right;
			}

			if(temp->right==NULL)
			{
				cout<<p->data<<" ";
				temp->right=p;
				p=p->left;
			}
			else
			{
				temp->right=NULL;
				p=p->right;
			}
		}
	}
}

void postorder(treenode* root)
{
	if(root==NULL)
		return ;

	postorder(root->left);
	postorder(root->right);
	cout<<root->data<<" ";
}

void morrispostorder(treenode* root)
{

	if(root==NULL)
		return;

	treenode* droot=createnode(-1);
	droot->left=root;

	treenode* p=droot;

	while(p!=NULL)
	{
		if(p->left==NULL)
		{
			p=p->right;
		}
		else
		{
			treenode* temp=p->left;
			while(temp->right!=NULL && temp->right!=p)
				temp=temp->right;

			if(temp->right==NULL)
			{
				temp->right=p;
				p=p->left;
			}
			else
			{
				treenode * mid=p->left;
				treenode* start=p,*end;

				while(mid!=p)
				{
					end=mid->right;
					mid->right=start;
					start=mid;
					mid=end;

				}

				start=p;
				mid=temp;

				while(mid!=p)
				{
					cout<<mid->data<<" ";
					
					end=mid->right;
					mid->right=start;
					start=mid;
					mid=end;

				}

				temp->right=NULL;
				p=p->right;
			}
		}
	}
}


int main()
{
	treenode* root=takeinput();
	inorder(root);
	cout<<endl;
	morrisinorder(root);
	cout<<endl;
	preorder(root);
	cout<<endl;
	morrispreorder(root);
	cout<<endl;
	postorder(root);
	cout<<endl;
	morrispostorder(root);
	cout<<endl;
	return 0;
}
