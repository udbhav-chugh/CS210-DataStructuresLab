#include<iostream>
#include<stack>
using namespace std;

struct treenode
{
	int data;
	treenode* left;
	treenode* right;
};

treenode* createnode(int d)
{
	treenode * temp=new treenode;
	temp->data=d;
	temp->left=NULL;
	temp->right=NULL;
}

treenode* find(int num, treenode*root)
{
	if(root==NULL)
	return NULL;
	
	if(root->data==num)
	return root;
	
	treenode* temp=find(num,root->left);
	if(temp!=NULL)
	return temp;
	
	temp=find(num,root->right);
	return temp;
}

void setleft(treenode*temp, treenode* newtemp)
{
	if(temp->left==NULL)
	temp->left=newtemp;
}

void setright(treenode*temp, treenode* newtemp)
{
	if(temp->right==NULL)
	temp->right=newtemp;
}


void inorder1(treenode* root)
{
	if(root==NULL)
	return;
	
	inorder1(root->left);
	cout<<root->data<<" ";
	inorder1(root->right);

}

void inorder2(treenode* root)
{
  if(root==NULL)
    return ;
  stack<treenode*> st;

  treenode* temp=root;
  do
    {
      while(temp!=NULL)
	{
	  st.push(temp);
	  temp=temp->left;
	}
      if(!st.empty())
	{
	  cout<<st.top()->data<<" ";
	  temp=st.top()->right;
	  st.pop();
	  
	}
    }while(!st.empty() || temp!=NULL );

}

void preorder1(treenode* root)
{
  if(root==NULL)
    return;
  cout<<root->data<<" ";
  preorder1(root->left);
  preorder1(root->right);
}

void preorder2(treenode* root)
{
  if(root==NULL)
    return;
    
  stack<treenode*> st;

  treenode* temp=root;
  do
    {
      while(temp!=NULL)
	{
	  cout<<temp->data<<" ";
	  st.push(temp);
	  temp=temp->left;
	}

      if(st.empty()==0)
	{
	  temp=st.top()->right;
	  st.pop();
	}
    }while(!st.empty() || temp!=NULL);
}

void postorder1(treenode * root)
{
  if(root==NULL)
    return;
  postorder1(root->left);
  postorder1(root->right);
  cout<<root->data<<" ";
}

void postorder2( treenode* root)
{

    // Check for empty tree
    if (root == NULL)
        return;
     
    struct Stack* stack = createStack(MAX_SIZE);
    do
    {
        // Move to leftmost node
        while (root)
        {
            // Push root's right child and then root to stack.
            if (root->right)
                push(stack, root->right);
            push(stack, root);
 
            // Set root as root's left child  
            root = root->left;
        }
 
        // Pop an item from stack and set it as root    
        root = pop(stack);
 
        // If the popped item has a right child and the right child is not
        // processed yet, then make sure right child is processed before root
        if (root->right && peek(stack) == root->right)
        {
            pop(stack);  // remove right child from stack
            push(stack, root);  // push root back to stack
            root = root->right; // change root so that the right 
                                // child is processed next
        }
        else  // Else print root's data and set root as NULL
        {
            printf("%d ", root->data);
            root = NULL;
        }
    } while (!isEmpty(stack));
	                                                       
} 
  

int main()
{
	int n;
	cin>>n;
	int parent,num;
	char ch;
	cout<<"enter root ";
	cin>>num;
		
	treenode * root=createnode(num);
	
	for(int i=1;i<n;i++)
	{
		cout<<"enter parent, child, left/right: ";
		cin>>parent>>num>>ch;
		
		treenode* temp=find(parent,root);
		if(temp==NULL)
		  {
		    cout<<"Try again root not in tree"<<endl;
		    i--;
		    continue;
		  }
		treenode * newtemp=createnode(num);
		if(ch=='L')
		  {
		     if(temp->left!=NULL)
		      {  cout<<"left already filled try again"<<endl;
		     	i--;
		      }
		     else
		      setleft(temp,newtemp);
		  }
		else
		  {
		    if(temp->right!=NULL)
		      {
			cout<<"right already filled try again"<<endl;
			i--;
		      }
		    else
		      setright(temp,newtemp);
		  }
	}
	
	inorder1(root);
	cout<<endl;
	inorder2(root);
	cout<<endl;
	preorder1(root);
	cout<<endl;
	preorder2(root);
	cout<<endl;
	postorder1(root);
	cout<<endl;
	postorder2(root);
	cout<<endl;
	return 0;

}
	

