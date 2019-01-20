#include<iostream>
using namespace std;

//structure to store nodes of tree
struct treenode
{
	int data;
	treenode* left;
	treenode* right;
	bool rightthread;
};

//creates nodes of tree
treenode* createnode(int d)
{
	treenode* temp=new treenode;
	temp->data=d;
	temp->left=NULL;
	temp->right=NULL;
	temp->rightthread=0;
	return temp;
}

//finds the parent element of the input child
treenode* find(treenode* root, int parent)
{
	if(root==NULL)
		return NULL;
	if(root->data==parent)
		return root;
	treenode* temp=find(root->left,parent);
	
	if(temp!=NULL)
		return temp;
	else if(root->rightthread==0)
		return find(root->right,parent);
	else
	return NULL;
}

//inserts in left and updates threads of child and parent and if elemnt already present, displays error message
void setleft(treenode* parent, int child)
{
	if(parent->left!=NULL)
	{
		cout<<parent->left->data<<" is already present at the specified position for "<<child<<endl;
	}
	else
	{
		treenode* childtemp=createnode(child);
		parent->left=childtemp;
		childtemp->rightthread=1;
		childtemp->right=parent;
	}

}

//inserts in right and updates threads of child and parent and if elemnt already present, displays error message
void setright(treenode* parent, int child)
{
	if(parent->right!=NULL && parent->rightthread==0)
	{
		cout<<parent->right->data<<" is already present at the specified position for "<<child<<endl;
	}
	else
	{
		treenode* childtemp=createnode(child);
		childtemp->right=parent->right;
		parent->right=childtemp;
		parent->rightthread=0;
		if(childtemp->right==NULL)
			childtemp->rightthread=0;
		else
		childtemp->rightthread=1;
	}

}

//to take input in required format
treenode* takeinput()
{
	int n; //no of inputs
	cin>>n;
	int child,parent;
	char pos;
	cin>>child>>parent>>pos; ////input of root

	treenode* root=createnode(child);//creating root of tree
	
	for(int i=0;i<n-1;i++)
	{
		cin>>child>>parent>>pos;
		treenode* parenttemp=find(root,parent);

		if(parent==-1)//if root is created again
		{
			cout<<root->data<<"is already present at the specified position for "<<child<<endl; //if we try to create root again
		}
		if(find(root,parent)==NULL) // if parent not present again it is an error
			{
				if(parent !=-1) //since for -1 we are already displaying error message above
					cout<<parent<<" not found"<<endl;
				continue;
			}
		
		if(pos=='L') //checks left child or rightchild insertion
			setleft(parenttemp,child);
		else
			setright(parenttemp,child);
		
	}
	return root;
}

//to return elemnt present at leftmost position of give root node
treenode* leftmost(treenode* root)
{
	treenode* temp=root;
	while(temp->left!=NULL)
	{
		temp=temp->left;
	}
	return temp;
}

//function to print inorder traversal using threads
void threadinorder(treenode* root)
{
	bool flag=0;//flag maintains when we have to go to leftmost and when not to
	treenode* temp=root;

	while(temp!=NULL)
	{
		if(!flag)
		temp=leftmost(temp);

		cout<<temp->data;
		if(temp->rightthread==1)
			cout<<"T"<<" ";
		else
			cout<<" ";

		if(temp->rightthread)
		{
			
			temp=temp->right;
			flag=1;
		}
		else
		{
			temp=temp->right;
			flag=0;
		}
	}
}

int main()
{
	//call function to take input
	treenode* root=takeinput();
	cout<<endl;
	//call function to print inorder traversal

	threadinorder(root);
	cout<<endl;


	return 0;
}
