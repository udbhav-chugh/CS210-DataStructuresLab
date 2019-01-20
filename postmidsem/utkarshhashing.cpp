#include<iostream>
#include<bits/stdc++.h>
using namespace std;

typedef long long int lli;

class HashTable
{
	int size;
	list <int> *tab;
public:
	HashTable(int n);
	bool search(int n);
	void ins(int n);
	void del(int n);
	void printTable();
	void delTable();
	int calcHash(int n);
};
HashTable :: HashTable(int n)
{
	this->size=n;
	this->tab=new list <int> [n];
}
int HashTable:: calcHash(int n)
{
	return n%(this->size);
}
bool HashTable:: search(int n)
{
	int index=calcHash(n);
	list <int> l= (this->tab[index]);
	for(list <int>::iterator itr=l.begin();itr!=l.end();itr++)
	{
		if(*itr==n)
			return true;
	}
	return false;	
}
void HashTable:: ins(int n)
{
	int index=calcHash(n);
	(this->tab[index]).push_back(n);	
}
void HashTable:: del(int n)
{
	int index=calcHash(n);
	(this->tab[index]).remove(n);
		
}
void HashTable:: printTable()
{
	for(int i=0;i<size;i++)
	{
		cout<<"Bucket "<<i<<" : ";
		list <int>::iterator itr;
		for(itr=(this->tab[i]).begin();itr!=(this->tab[i]).end();itr++)
			cout<<*itr<<" ";
		cout<<endl;
	}
}
void HashTable:: delTable()
{
	delete this->tab;
}
int main()
{
	int ch;
	cout<<"Enter size";
	int s;
	cin>>s;
	HashTable *h1=new HashTable(s);
	while(1)
	{
		cout<<"Enter your choice 1 for insert , 2 delete, 3 search , 4 print ";
		cin>>ch;
		if(ch==1)
		{
			cin>>s;
			h1->ins(s);
		}
		else if(ch==2)
		{
			cin>>s;
			h1->del(s);
		}
		else if(ch==3)
		{
			cin>>s;
			if(h1->search(s))
				cout<<"Found\n";
			else
				cout<<"Not Found\n";
		}
		else if(ch==4)
		{
			h1->printTable();
		}
		else
			break;
	}

	return 0;
}
