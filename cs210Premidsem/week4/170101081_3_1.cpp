#include<iostream>
using namespace std;


//structure to store nodes of tree
struct treenode
{
	int data;
	treenode* left;
	treenode* right;
};

//structure to store nodes of stack
//we push treenode pointers in stack
struct node
{
	treenode* data;
	node* next;
};


struct stack
{
	node* top; //gives top pointer of stack
	int size; // to store size of stack
};


//initalises top with null and size with zero
stack* createstack()
{
	stack * temp=new stack;
	temp->top=NULL;
	temp->size=0;
	return temp;
}

//creates node of stack with given input d
node* cnode(treenode* d)
{
	node* temp=new node;
	temp->data=d;
	temp->next=NULL;
	return temp;
}

//pushes node of stack onto stack
void push(stack * st, treenode* d)
{
	node* temp=cnode(d);

	if(st->top==NULL)//stack empty
		st->top=temp;
	else
	{
		temp->next=st->top;
		st->top=temp;
	}
	st->size++;//increment stack size
}

//to delete top element of stack
void pop(stack * st)
{
	if(st->top==NULL)//if stack is empty nothing can be deleted
		return;
	node* temp=st->top;
	st->top=st->top->next;
	delete temp;

	st->size--;//decrement stacksize
}

//returns top elemnt of stack
treenode* top(stack* st)
{
	if(st->top==NULL)
		return NULL;//if stack is empty returns NULL

	return st->top->data;
}

//returns true id stack empty false otherwise
bool isempty(stack * st)
{
	if(st->top==NULL)
		return 1;
	else
		return 0;
}

//returns stacksize
int getsize(stack * st)
{
	return st->size;
}


//creates nodes of tree
treenode* createnode(int d)
{
	treenode* temp=new treenode;
	temp->data=d;
	temp->left=NULL;
	temp->right=NULL;
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
	else
		return find(root->right,parent);
}

//inserts in left and if elemnt already present, displays error message
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
	}

}

//inserts in right and if elemnt already present, displays error message
void setright(treenode* parent, int child)
{
	if(parent->right!=NULL)
	{
		cout<<parent->right->data<<" is already present at the specified position for "<<child<<endl;
	}
	else
	{
		treenode* childtemp=createnode(child);
		parent->right=childtemp;
	}

}

//to take input in required format
treenode* takeinput()
{
	int n; //no of inputs
	cin>>n;
	int child,parent;
	char pos;
	cin>>child>>parent>>pos; //input of root

	treenode* root=createnode(child); //creating root of tree
	
	for(int i=0;i<n-1;i++)
	{
		cin>>child>>parent>>pos;
		treenode* parenttemp=find(root,parent);

		if(parent==-1)
		{
			cout<<root->data<<"is already present at the specified position for "<<child<<endl; //if we try to create root again
		}		
		if(find(root,parent)==NULL) // if parent not present
			{
				if(parent !=-1) //since for -1 we are already displaying error message
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

//function to print inorder traversal using stack
void stackinorder(treenode* root)
{
	//checks empty stack
	if(root==NULL)
		return;


	int maxstackdepth=0,maxdepth=0; //maxdepth stores the final ans of maxstackdepth
	stack *st=createstack(); //creates stack
	treenode* temp=root;
	do
	{
		//push all elemnts until we reach leftmost
		while(temp!=NULL)
		{

			push(st,temp);
			maxstackdepth++;

			if(maxstackdepth>maxdepth)
				maxdepth=maxstackdepth; //update maxdepth
			
			temp=temp->left;
		}

		//checks stack is not empty
		if(!isempty(st))
		{
			
			cout<<top(st)->data<<" ";
			temp=top(st)->right;
			pop(st);
			maxstackdepth--;

		}

	}while(!isempty(st) || temp!=NULL);//if both are false it means traversal is complete

	cout<<endl<<maxdepth<<endl;
}

//to calculate height of tree
int height(treenode* root)
{
	if(root==NULL)
		return 0;
	int temp1=height(root->left);
	int temp2=height(root->right);
	if(temp1>temp2)
		return temp1+1;
	else
		return temp2+1;
}

int main()
{
	//call function to take input
	treenode* root=takeinput();
	cout<<endl;

	//call function to print inorder traversal
	stackinorder(root);
	//to print height
	cout<<height(root)-1<<endl;


	return 0;
}
