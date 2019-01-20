#include<iostream>
#include<bits/stdc++.h>
using namespace std;

typedef long long int lli;

typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
	struct node *parent;
	int height;
} Node;
class avl
{
	Node *root;
public:
	avl();
	Node *getroot();
	void itraverse(Node *n);
	Node * search(int n);
	Node *createNode(int n);
	void rebalance(vector <Node *> v);
	void insert(int n);
	void lrot(Node *n);
	void rrot(Node *n);
	void delNode(int n);
	int getlheight(Node *n);
	int getrheight(Node *n);
};
avl :: avl()
{
	this->root=NULL;
}
Node* avl::getroot()
{
	return this->root;
}
void avl:: itraverse(Node *n)
{
	//cout<<"Hell0";
	if(n==NULL)
		return;
	this->itraverse(n->left);
	cout<<n->data<<' ';
	if(n->left)
		cout<<n->left->data<<' ';
	else
		cout<<"-- ";
	if(n->right)
		cout<<n->right->data<<' ';
	else
		cout<<"-- ";
	cout<<endl;
	this->itraverse(n->right);
}
Node * avl:: search(int n)
{
	Node *p=this->root;
	while(p)
	{
		if(p->data==n)
			return p;
		if(p->data<n)
			p=p->right;
		else
			p=p->left;
	}
	return NULL;
}
Node * avl:: createNode(int n)
{
	Node *newNode=new Node;
	newNode->data=n;
	newNode->parent=NULL;
	newNode->left=NULL;
	newNode->right=NULL;
	newNode->height=1;
}
void avl:: rrot(Node *n)
{
	int temp=n->data;
	n->data=(n->left)->data;
	(n->left)->data=temp;

	Node *x=n->left;
	n->left=x->left;
	if(n->left)
		n->left->parent=n;

	x->left=x->right;

	x->right=n->right;
	if(x->right)
		x->right->parent=x;

	n->right=x;
	x->parent=n;

	x->height=max(this->getlheight(x),this->getrheight(x))+1;
	n->height=max(this->getlheight(x),this->getrheight(x))+1;

}
void avl:: lrot(Node *n)
{
	
	int temp=n->data;
	n->data=(n->right)->data;
	(n->right)->data=temp;

	Node *x=n->right;
	n->right=x->right;
	if(n->right)
		n->right->parent=n;

	x->right=x->left;

	x->left=n->left;
	if(x->left)
		x->left->parent=x;

	n->left=x;
	x->parent=n;

	x->height=max(this->getlheight(x),this->getrheight(x))+1;
	n->height=max(this->getlheight(x),this->getrheight(x))+1;

}
int avl::getlheight(Node *n)
{
	if(n->left)
		return n->left->height;
	else
		return 0;
}
int avl::getrheight(Node *n)
{
	if(n->right)
		return n->right->height;
	else
		return 0;
}
void avl::rebalance(vector <Node *> v)
{
	cout<<"inside rebalance\n";
	for(int i=v.size()-1;i>=0;i--)
	{
		if(abs(this->getlheight(v[i]) - this->getrheight(v[i]))<=1)
		{
			v[i]->height=max(this->getlheight(v[i]),this->getrheight(v[i]))+1;
		}
		else
		{
			//v[i]==first unbalanced node
			cout<<"Rebalancing\n";
			int c=0;
			if(v[i+1]==(v[i]->right))
				c+=1;
			if(v[i+2]==(v[i+1]->right))
				c+=2;
			
			switch(c)
			{
				case 0:
				this->rrot(v[i]);
				break;

				case 1:
				this->rrot(v[i+1]);
				this->lrot(v[i]);
				break;

				case 2:
				this->lrot(v[i+1]);
				this->rrot(v[i]);
				break;

				case 3:
				this->lrot(v[i]);				
				break;
			}

		}
	}
	
}
void avl::insert(int n)
{
	if(this->search(n))
	{
		cout<<"Key already exists Could not insert key\n";
		return;
	}
	
	Node *newNode=createNode(n);
	vector <Node *> v;
	Node *p=this->root;
	if(p==NULL)
	{
		this->root=newNode;
		return;
	}
	v.push_back(p);
	while(1)
	{
		if(p->data >= n )
		{
			if(p->left == NULL)
			{
				p->left=newNode;
				newNode->parent=p;
				break;
			}
			else
			{
				p=p->left;
				v.push_back(p);
			}
		}
		else
		{
			if(p->right == NULL)
			{
				p->right=newNode;
				newNode->parent=p;
				break;
			}
			else
			{
				p=p->right;
				v.push_back(p);
			}
		}	
	}
	v.push_back(newNode);
	cout<<"Key inserted\n";
	this->rebalance(v);
	
}
void avl::delNode(int n)
{
	if(!(this->search(n)))
	{
		cout<<"Key does not exist Could not delete key\n";
		return;
	}
	vector <Node *> v;
	Node *p=this->root;
	while(1)
	{
		v.push_back(p);
		if(p->data > n)
			p=p->left;
		else if(p->data < n)
			p=p->right;
		else
			break;
	}
	while(1)
	{
		cout<<"loop\n";
		Node *temp=v[v.size()-1];
		Node *cur=temp->left;
		if(temp->left!=NULL && temp->right!=NULL)
		{
			//Finding predecessor
			v.push_back(cur);
			while(cur->right)
			{
				cur=cur->right;
				v.push_back(cur);
			}
			int x=temp->data;
			temp->data=cur->data;
			cur->data=x;
		}
		else
			break;
	}
	//deletion
	Node * target=v[v.size()-1];
	Node * ptarget=(v.size()-1)?v[v.size()-2]:NULL;
	if(target->left==NULL && target->right==NULL)
	{
		if(ptarget==NULL)
		{
			this->root=NULL;
		}
		else
		{
			if(ptarget->left==target)
				ptarget->left=NULL;
			else if(ptarget->right==target)
				ptarget->right=NULL;
		}
	}
	else if(target->left==NULL)
	{
		if(ptarget==NULL)
		{
			this->root=target->right;
		}
		else
		{
			if(ptarget->left==target)
			{
				ptarget->left=target->right;
				target->right->parent=ptarget;
			}
			else if(ptarget->right==target)
			{
				ptarget->right=target->right;
				target->right->parent=ptarget;
			}
		}
	}
	else if(target->right==NULL)
	{
		if(ptarget==NULL)
		{
			this->root=target->left;
		}
		else
		{
			if(ptarget->left==target)
			{
				ptarget->left=target->left;
				target->left->parent=ptarget;
			}
			else if(ptarget->right==target)
			{
				ptarget->right=target->left;
				target->left->parent=ptarget;
			}
		}
	}
	v.pop_back();
	// delete target;
	this->rebalance(v);

}
int main()
{
  avl* tree = NULL;
  int key;
  int choice;

  do{
	  cout << "1. Create new tree" << endl;
  	cout << "2. Add new key to the tree" << endl;
	  cout << "3. Search a key in the tree" << endl;
  	cout << "4. Delete a key from the tree" << endl;
  	cout << "5. Inorder traversal of the tree" << endl;
  	cout << "Any other choice to exit" << endl;
  	cout << "Enter your choice:";
  	cin >> choice;
  	cout << "You entered " << choice << endl;
    
    switch(choice){
      case 1:
        tree = new avl();
        break;

      case 2:
        if(tree == NULL){
          cout << "Create a new tree first" << endl;
          break;
        }
        cout << "Enter key to add \n";
        cin >> key;
        tree->insert(key);
        break;

      case 3:
        if(tree == NULL){
          cout << "Create a new tree first" << endl;
          break;
        }
        cout << "Enter key to search    ";
        cin >> key;
        if(tree->search(key) == NULL){
          cout << "Key " << key <<" not found." << endl;
        }else{
          cout << "Key " << key << "found" << endl;
        }
        break;

      case 4:
        if(tree == NULL){
          cout << "Create a new tree first" << endl;
          break;
        }
        cout << "Enter key to delete    ";
        cin >> key;
        if(tree->search(key) == NULL){
          cout << "Key " << key << " not found." << endl;
        }else{
          tree->delNode(key);
        }
        break;

      case 5:
        if(tree == NULL){
          cout << "Create a new tree first" << endl;
          break;
        }
        tree->itraverse(tree->getroot());
        break;

      default:
        return(0);
    }
  }
  while(true);
    return 0;

}
