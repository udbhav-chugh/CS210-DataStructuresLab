#include<bits/stdc++.h>
using namespace std;


int hashfunc(int val,int n)
{
	return val%n;
}

class node
{
public:
	int data;
	node* next;

	node(int d)
	{
		data=d;
		next=NULL;
	}
};


class hashtab
{
public:
	int bucketsize;
	node* *arr;
	int keynum;
	double maxkeys;

	hashtab(int size,int maxkey);
	void insert(int val);
	int search(int val);
	int del(int val);
	void ptable();
};

hashtab:: hashtab(int size,int maxkey)
{
	bucketsize=size;
	maxkeys=maxkey;
	keynum=0;
	arr=new node*[size];
	for(int i=0;i<bucketsize;i++)
		arr[i]=NULL;
}

void hashtab:: insert(int val)
{
	int hashval=hashfunc(val,bucketsize);
	node* temp=new node(val);
	keynum++;

	if(arr[hashval]==NULL)
		arr[hashval]=temp;
	else
	{
		node * t=arr[hashval];
		while(t->next!=NULL)
		{
			t=t->next;
		}
		t->next=temp;
	}
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
		cout<<"Bucket "<<i<<":\t";
		while(temp!=NULL)
		{
			if(temp->next==NULL)
				cout<<temp->data;
			else
				cout<<temp->data<<", ";
			
			temp=temp->next;
		}
		cout<<endl;
	}
}

int main()
{
	double load;
	int n;
	cin>>load;
	cin>>n;
	double maxkey=load*n;
	hashtab *h=new hashtab(n,maxkey);
	hashtab *h2;
	int val;
	while(cin>>val)
	{
		if(h->search(val)!=-1)
		{
			cout<<"Key "<<val<<" already present in the hash table. Status of the hash table.\nNumber of keys: "<<h->keynum<<"\nNumber of buckets: "<<h->bucketsize<<endl;
			h->ptable();
			cout<<endl;
		}
		else
		if((h->keynum+1)*(1.0)>maxkey)
		{
			while(maxkey<(h->keynum+1)*1.0)
			{
				n*=3;
				maxkey=load*n;
			}

			h2=new hashtab(n,maxkey);
			for(int i=0;i<h->bucketsize;i++)
			{
				node * temp=h->arr[i];
				while(temp!=NULL)
				{
					h2->insert(temp->data);
					temp=temp->next;
				}
			}
			h2->insert(val);

			for(int i=0;i<h->bucketsize;i++)
			{
				node * temp=h->arr[i];
				while(temp!=NULL)
				{
					int pp=temp->data;
					temp=temp->next;
					h->del(pp);
				}
			}

			delete [] h->arr;
			
			h=h2;
		}
		else
			h->insert(val);
	}
	return 0;

}