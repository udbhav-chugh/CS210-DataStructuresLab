#include<bits/stdc++.h>
using namespace std;

int hashfunc(int val,int n)
{
	return val%n;
}

class node
{

	int data;
	node* next;

public:
	node(int d)
	{
		data=d;
		next=NULL;
	}

	int getdata()
	{
		return data;
	}
	node * getnext()
	{
		return next;
	}

	void setnext(node * temp)
	{
		next=temp;
	}
};


class hashtab
{
	int bucketsize;
	node* *arr;

public:

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
}

void hashtab:: insert(int val)
{
	int hashval=hashfunc(val,bucketsize);
	node* temp=new node(val);
	node * t=arr[hashval];
	arr[hashval]=temp;
	temp->setnext(t);
}

int hashtab:: search(int val)
{
	int hashval=hashfunc(val,bucketsize);
	node * temp=arr[hashval];

	while(temp!=NULL)
	{
		if(temp->getdata()==val)
			return hashval;
		temp=temp->getnext();
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
		if(temp->getdata()==val)
			{
				if(prev==NULL)
				{
					arr[hashval]=temp->getnext();
					delete temp;
					return 1;
				}
				else
				{
					prev->setnext(temp->getnext());
					delete temp;
					return 1;
				}
			}
		prev=temp;
		temp=temp->getnext();
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
			cout<<temp->getdata()<<" ";
			temp=temp->getnext();
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
