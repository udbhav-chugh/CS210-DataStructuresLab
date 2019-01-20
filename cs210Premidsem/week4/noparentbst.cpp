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

treenode* insert(treenode* root, int d)
{
	if(root==NULL)
	{
		treenode* temp=createnode(d);
		return temp;
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
		y->left=createnode(d);
	else
		y->right=createnode(d);

	return root;

}

treenode* takeinput()
{
	int n;
	cin>>n;
	treenode* root=NULL;
	for(int i=0;i<n;i++)
	{
		int temp;
		cin>>temp;
		root=insert(root,temp);
	}
	return root;
}


treenode* minimum(treenode* root)
{
	if(root==NULL)
		return NULL;
	while(root->left!=NULL)
		root=root->left;
	return root;
}

treenode* search(treenode* root,int d)
{
	if(root==NULL)
		return NULL;
	if(root->data==d)
		return root;
	if(root->data>d)
		return search(root->left,d);
	
	return search(root->right,d);
}

treenode* successor(treenode* root, treenode* temp)
{
	if(temp->right!=NULL)
	{
		return minimum(temp->right);
	}

	treenode* ans=NULL;
	while(root!=NULL)
	{
		if(root->data>temp->data)
		{
			ans=root;
			root=root->left;
			
		}
		else
			if(root->data<temp->data)
			root=root->right;
		else
			break;
	}
	return ans;
}


treenode* deletenode(treenode* root, int d)
{
	
	if(root->data>d)
	{
		treenode* leftsub=deletenode(root->left,d);
		root->left=leftsub;
	}
	else
		if(root->data<d)
		{
			treenode* rightsub=deletenode(root->right,d);
			root->right=rightsub;
		}
	else
	{
		if(root->left==NULL)
		{
			treenode* temp=root;
			root=root->right;
			delete temp;
			return root;
		}
		else
			if(root->right==NULL)
			{
				treenode* temp=root;
				root=root->left;
				delete temp;
				return root;
			}
			else
			{
				treenode* succ=successor(root, root);
				int help=succ->data;
				treenode* temp1=deletenode(root,help);
				root->data=help;
				return root;
			}
	}
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
	cout<<endl;

	int l;
	cout<<"Enter number of nodes to be deleted: ";
	cin>>l;

	for(int i=0;i<l;i++)
	{
		int b;
		cin>>b;
		root=deletenode(root,b);
		inorder(root);
		cout<<endl;
	}
	return 0;
}