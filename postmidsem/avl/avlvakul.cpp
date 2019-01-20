#include <bits/stdc++.h>
using namespace std;

//WITH STRUCT
//SEARCH AND INSERT AND DELETE RECURSIVE 
//LEVEL ORDER AND PREORDER TRAVERSALS
//DUPLICATE KEYS HANDLED AS WELL

struct TreeNode{
	int key;
	TreeNode *left;
	TreeNode *right;
	int height;
	int count;//for duplicates
};

TreeNode *mkNode(int key){
	TreeNode *n=new TreeNode;
	n->key=key;
	n->left=NULL;
	n->right=NULL;
	n->height=1;
	n->count=1;
}

int height2(TreeNode *node){
	if(node==NULL){
		return 0;
	}
	return node->height;
}

int Difference(TreeNode *node){
	if(node==NULL){
		return 0;
	}
	return (height2(node->left)-height2(node->right));
}

void PrintLevelWise(TreeNode *root){
	if(root==NULL){
		return;
	}
	queue<TreeNode*> q;
	q.push(root);
	while(!q.empty()){
		TreeNode *n=q.front();
		for(int i=0;i<n->count;i++){
			cout<<n->key<<" ";
		}
		q.pop();
		if(n->left!=NULL){
			q.push(n->left);
		}
		if(n->right!=NULL){
			q.push(n->right);
		}
	}
}

TreeNode *RightRotate(TreeNode *root){
	TreeNode *y=root->left;
	TreeNode *T=y->right;
	y->right=root;
	root->left=T;

	root->height=max(height2(root->left),height2(root->right))+1;
	y->height=max(height2(y->left),height2(y->right))+1;
	return y;
}

TreeNode *LeftRotate(TreeNode *root){
	TreeNode *y=root->right;
	TreeNode *T=y->left;
	y->left=root;
	root->right=T;

	root->height=max(height2(root->left),height2(root->right))+1;
	y->height=max(height2(y->left),height2(y->right))+1;
	return y;
}

TreeNode *insert(TreeNode *root,int key){
	if(root==NULL){
		return mkNode(key);
	}
	if(root->key==key){
		root->count++;
		return root;
	}
	if(root->key>key){
		root->left=insert(root->left,key);
	}else{
		root->right=insert(root->right,key);
	}
	root->height=max(height2(root->left),height2(root->right))+1;
	int val=Difference(root);
	if(val>1 && root->left->key>key){
		return RightRotate(root);
	}
	if(val<-1 && root->right->key<key){
		return LeftRotate(root);
	}
	if(val>1 && root->left->key<key){
		root->left=LeftRotate(root->left);
		return RightRotate(root);
	}
	if(val<-1 && root->right->key>key){
		root->right=RightRotate(root->right);
		return LeftRotate(root);
	}
	return root;
}

TreeNode *search(TreeNode *root,int key){
	if(root==NULL){
		return NULL;
	}
	if(root->key==key){
		return root;
	}else{
		if(root->key>key){
			return search(root->left,key);
		}else{
			return search(root->right,key);
		}
	}
}

TreeNode *Leftmost(TreeNode *root){
	if(root==NULL){
		return NULL;
	}
	while(root->left!=NULL){
		root=root->left;
	}
	return root;
}

TreeNode *DeleteNode(TreeNode *root,int key){
	if(root==NULL){
		return NULL;
	}
	if(root->key==key){
		if(root->count>1){
			root->count--;
			return root;
		}
	}
	if(root->key>key){
		root->left=DeleteNode(root->left,key);
	}else{
		if(root->key<key){
			root->right=DeleteNode(root->right,key);
		}else{
			if(root->right==NULL && root->right==NULL){
				return NULL;
			}else{
			if(root->right==NULL && root->left!=NULL){
				TreeNode *temp=root;
				root=root->left;
				delete temp;
			}else{
				if(root->right!=NULL && root->left==NULL){
					TreeNode *temp=root;
					root=root->right;
					delete temp;
				}else{
					if(root->left!=NULL && root->right!=NULL){
						TreeNode *temp=Leftmost(root->right);
					    root->key=temp->key;
					    root->right=DeleteNode(root->right,temp->key);
					}
					
				}
			}
		}
		}
	}
	root->height=max(height2(root->left),height2(root->right))+1;
	int val=Difference(root);
	if(val>1 && root->left->key>key){
		return RightRotate(root);
	}
	if(val<-1 && root->right->key<key){
		return LeftRotate(root);
	}
	if(val>1 && root->left->key<key){
		root->left=LeftRotate(root->left);
		return RightRotate(root);
	}
	if(val<-1 && root->right->key>key){
		root->right=RightRotate(root->right);
		return LeftRotate(root);
	}
	return root;
}


void preOrder(TreeNode *root){
	if(root==NULL){
		return;
	}
	for(int i=0;i<root->count;i++){
		cout<<root->key<<" ";
	}
	preOrder(root->left);
	preOrder(root->right);
}



int main(){
	TreeNode *root=NULL;
	root=insert(root,10);
	root=insert(root,20);
	PrintLevelWise(root);
	cout<<endl;
	root=insert(root,30);
	PrintLevelWise(root);
	cout<<endl;
	root=insert(root,40);
	PrintLevelWise(root);
	cout<<endl;
	root=insert(root,50);
	PrintLevelWise(root);
	cout<<endl;
	root=insert(root,25);
	PrintLevelWise(root);
	cout<<endl;
	root=insert(root,20);
	//root=insert(root,25);
	//root=insert(root,50);
	if(!search(root,10)){
		cout<<"NOt present"<<endl;
	}
	root=DeleteNode(root,30);
	PrintLevelWise(root);
	cout<<endl;
	root=DeleteNode(root,40);
	PrintLevelWise(root);
	cout<<endl;
	root=DeleteNode(root,20);

	PrintLevelWise(root);
	//preOrder(root);
	cout<<endl;
}