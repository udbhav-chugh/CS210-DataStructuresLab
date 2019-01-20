#include<iostream>
#include<time.h>
using namespace std;

void swap(int &x, int &y)
{
	int temp=x;
	x=y;
	y=temp;
}


void topdown( int * input, int * heap,int heapsize)
{

	int n=0;
	for(int i=1;i<=heapsize;i++)
	{
		n++;
		int var;
		cin>>var;
		heap[n]=var;

		int parent=i/2,child=n;
		while(parent>0)
		{
			if(heap[parent]>heap[child])
				break;
			
			swap(heap[parent],heap[child]);

			parent=parent/2;
			child=child/2;
		}
	}

}

int max(int *heap,int i,int l,int r,int heapsize)
{
	int largest=i;

	if(l<=heapsize && heap[l]>heap[i])
		largest=l;
	if(r<=heapsize && heap[r]>heap[largest])
		largest =r;
	return largest;
}

void maxheapify(int * heap, int i,int heapsize)
{
	int l=2*i,r=2*i+1;
	int x=max(heap,i,l,r,heapsize);

	if(x!=i)
	{
		swap(heap[x],heap[i]);
		maxheapify(heap,x,heapsize);
		
		
	}

}


void bottomup(int * input, int *heap,int heapsize)
{

	int n=0;

	for(int i=1;i<=heapsize;i++)
	{
		heap[++n]=input[i];
	}

	for(int i=heapsize/2;i>=1;i--)
	maxheapify(heap,i,heapsize);
}


void heapsort(int * input, int * heap, int heapsize)
{
	bottomup(input,heap,heapsize);
	while(heapsize>=1)
	{
		swap(heap[1],heap[heapsize]);
		heapsize--;
		maxheapify(heap,1,heapsize);
	}
}

int takeinput(int *input,int maxheapsize)
{
	int n;
	cout<<"no of elements in heap: ";
	cin>>n;
	if(n>maxheapsize)
	{
		cout<<"exceed size"<<endl;
		return -1;
	}

	for(int i=1;i<=n;i++)
		cin>>input[i];
	return n;

}


int main()
{
	int maxheapsize=99;
	int input[100];
	int heapsize=-1;
	int heap[100];
	int method;
	
	while(heapsize==-1)
		heapsize=takeinput(input,maxheapsize);
	
	cout<<"method: ";
	cin>>method;
	if(method==1)
		{
			clock_t start=clock();
			topdown(input, heap,heapsize);
			clock_t end=clock();
			cout<<endl<<end-start<<endl;
		}
	else
	{
		clock_t start=clock();
		bottomup(input, heap,heapsize);
		clock_t end=clock();
		cout<<endl<<end-start<<endl;
	}

	for(int i=1;i<=heapsize;i++)
		cout<<heap[i]<<" ";
	cout<<endl;

	heapsort(input, heap,heapsize);
for(int i=1;i<=heapsize;i++)
		cout<<heap[i]<<" ";
	cout<<endl;

	cout<<endl;
	return 0;
}

