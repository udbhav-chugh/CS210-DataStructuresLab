#include<iostream>
using namespace std;

struct maxheap
{
	int key[101];
	int data[101];
	int maxheapsize;
	int heapsize;
};

void swap(int &x, int &y)
{
	int temp=x;
	x=y;
	y=temp;
}

void moveup(maxheap* h,int i)
{
	int child=i;
	int parent=child/2;

	while(parent>0 && h->key[parent]<h->key[child])
	{
		swap(h->key[parent],h->key[child]);
		swap(h->data[parent],h->data[child]);
	}
}

int largest(maxheap* h, int i, int l, int r)
{
	int lar=i;
	if(l<=h->heapsize && h->key[l]>h->key[lar])
		lar=l;
	if(r<=h->heapsize && h->key[r]>h->key[lar])
		lar=r;
	return lar;
}

void maxheapify(maxheap* h, int i)
{
	int l=2*i,r=2*i+1;
	int x=largest(h,i,l,r);
	if(x!=i)
	{
		swap(h->key[i],h->key[x]);
		swap(h->data[i],h->data[x]);
		maxheapify(h,x);

	}
}

void insert(maxheap* h, int k, int d)
{

	int t=++h->heapsize;

	if(t>h->maxheapsize)
	{
		h->heapsize--;
		cout<<"limit exceeded"<<endl;
		return;
	}

	h->key[t]=k;
	h->data[t]=d;
	moveup(h,h->heapsize);
}

void deletee(maxheap * h,int index)
{
	swap(h->key[index],h->key[h->heapsize]);
	swap(h->data[index],h->data[h->heapsize]);
	if(h->key[index]>h->key[h->heapsize])
		{
			h->heapsize--;
			moveup(h,index);
		}

	else
	{
		h->heapsize--;
		maxheapify(h,index);
	}
}

int getmax(maxheap* h)
{
	return h->data[1];
}

int extractmax(maxheap* h)
{
	int temp= h->data[1];
	deletee(h,1);
	return temp;
}

void merge(maxheap* newh, maxheap* h1, maxheap* h2)
{
	if(h1->heapsize+h2->heapsize>newh->maxheapsize)
	{
		cout<<"cannot merge"<<endl;
		return;
	}

	for(int i=1;i<=h1->heapsize;i++)
	{
		newh->heapsize++;
		newh->key[i]=h1->key[i];
		newh->data[i]=h1->data[i];
		
	}

	for(int i=1;i<=h2->heapsize;i++)
	{
		int j=++newh->heapsize;
		newh->key[j]=h2->key[i];
		newh->data[j]=h2->data[i];
	}

	for(int i=newh->heapsize/2;i>=1;i--)
		maxheapify(newh,i);
}

void increasekey(maxheap * h, int index, int x)
{
	if(x<h->key[index])
	{
		cout<<"error";
		return;
	}

	h->key[index]=x;
	moveup(h,index);
}

int main()
{
	maxheap * h=new maxheap;
	h->maxheapsize=100;
	h->heapsize=0;
	/*int option;
	cout<<"choose:\n1)insert\n2)delete\n3)getmax\n4)extractmax\n5)increasekey\n6)quit\n"
	cin>>option;

	while(option!=6)
	{
		switch(option)
		{
			case 1: insert(h);break;
			case 2: deletee(h);break;
			case 3: getmax(h);break;
			case 4: extractmax(h);break;
			case 5: increasekey(h);break;

		}
	}

	*/

	for(int i=1;i<=5;i++)
		insert(h,i,i);

	for(int i=1;i<=3;i++)
		deletee(h,i);

	cout<<endl<<getmax(h);
	extractmax(h);
	increasekey(h,1,5);
	cout<<endl<<getmax(h);
	return 0;

}