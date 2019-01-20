#include<bits/stdc++.h>
using namespace std;

int hashfunc(int val,int n)
{
	return val%n;
}

struct node
{

	int data;
	node* next;

	node(int d)
	{
		data=d;
		next=NULL;
	}
};


struct hashtab
{
	int bucketsize;
	node* *arr;

	hashtab(int size);
	void insert(int val);
	int search(int val);
	int del(int val);
	void ptable();
};

hashtab:: hashtab(int size)
{
	bucketsize=size;
	arr=new node*[size];
	for(int i=0;i<bucketsize;i++)
		arr[i]=NULL;
}

void hashtab:: insert(int val)
{
	int hashval=hashfunc(val,bucketsize);
	node* temp=new node(val);
	node * t=arr[hashval];
	arr[hashval]=temp;
	temp->next=t;

	//to insert at end
	/*if(arr[hashval]==NULL)
		arr[hashval]=temp;
	else
	{
		node * t=arr[hashval];
		while(t->next!=NULL)
		{
			t=t->next;
		}
		t->next=temp;
	}*/
}

int hashtab:: search(int val)
{
	int hashval=hashfunc(val,bucketsize);
	node * temp=arr[hashval];

	while(temp!=NULL)
	{
		if(temp->data==val)
			return hashval;
		temp=temp->next ;
	}

	return -1;
}

int hashtab:: del(int val)
{

	int hashval=hashfunc(val,bucketsize);
	node * temp=arr[hashval];
	node * prev=NULL;

	while(temp!=NULL)
	{
		if(temp->data==val)
			{
				if(prev==NULL)
				{
					arr[hashval]=temp->next;
					delete temp;
					return 1;
				}
				else
				{
					prev->next=temp->next;
					delete temp;
					return 1;
				}
			}
		prev=temp;
		temp=temp->next;
	}

	return 0;
}

void hashtab:: ptable()
{
	for(int i=0;i<bucketsize;i++)
	{
		node * temp=arr[i];
		cout<<"BUCKET "<<i<<": ";
		while(temp!=NULL)
		{
			cout<<temp->data<<" ";
			temp=temp->next;
		}
		cout<<endl;
	}
}
int main()
{
	int n;
	int val,option;
	hashtab *h=NULL;

	do
	{
		cout<<"\nSelect option:\n1)Create hashtabtable\n2)Insert\n3)Search value\n4)Delete value\n5)Print table\nAny other value to Exit\n";
		cin>>option;

	switch(option)
	{
		case 1: 
			{
				cout<<"Enter number of buckets: ";
				cin>>n;
				h=new hashtab(n);
				break;
			}
		case 2:
			{
				if(h==NULL)
				{
					cout<<"create table first\n";
					break;
				}
				cout<<"Enter value: ";
				cin>>val;
				h->insert(val);
				break;
			}
		case 3:
			{
				if(h==NULL)
				{
					cout<<"create table first\n";
					break;
				}
				cout<<"Enter value: ";
				cin>>val;
				int temp=h->search(val);
				if(temp==-1)
					cout<<val<<" not found\n";
				else
					cout<<val<<" found at bucket number: "<<temp<<endl;

				break;
			}

		case 4:
			{
				if(h==NULL)
				{
					cout<<"create table first\n";
					break;
				}
				cout<<"Enter value: ";
				cin>>val;
				int temp=h->del(val);

				if(temp==0)
					cout<<val<<" not found\n";
				else
					cout<<val<<" deleted.\n";

				break;
			}
		case 5:
			{
				if(h==NULL)
				{
					cout<<"create table first\n";
					break;
				}
				h->ptable();
				break;
			}

		default: 
		{
			return 0;
		}
	}

	}while(1);
}