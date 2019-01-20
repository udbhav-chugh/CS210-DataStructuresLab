#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

void swap(int &x, int &y)
{
	int temp=x;
	x=y;
	y=temp;
}

void moveup(int *heap,int i)
{
	int parent=i/2;
	int child=i;

	while(parent >0 && heap[parent]<heap[child])
	{
		swap(heap[parent],heap[child]);
		parent/=2;
		child/=2;
	}
}

void topdown(int * heap,int heapsize)
{

	for(int i=1;i<=heapsize;i++)
	{
		moveup(heap,i);
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


void bottomup(int *heap,int heapsize)
{

	for(int i=heapsize/2;i>=1;i--)
	maxheapify(heap,i,heapsize);
}


void heapsort(int * heap, int heapsize)
{
	bottomup(heap,heapsize);
	while(heapsize>=1)
	{
		swap(heap[1],heap[heapsize]);
		heapsize--;
		maxheapify(heap,1,heapsize);
	}
}

/*int takeinput(int *heap,int maxheapsize)
{
	int n;
	cout<<"no of elements in heap: ";
	cin>>n;
	if(n>maxheapsize)
	{
		cout<<"size exceeded"<<endl;
		return -1;
	}

	for(int i=1;i<=n;i++)
		cin>>heap[i];
	return n;

}*/


int main()
{
	int maxheapsize=1000000;
	int heapsize=-1;
	int heap[1000001];
	int method;
	//while(heapsize==-1)
	//	heapsize=takeinput(heap,maxheapsize);
	
	cin>>heapsize;
	srand(time(0));
	for(int i=1;i<=heapsize;i++)
		heap[i]=rand();
	cout<<"method: ";
	cin>>method;
	if(method==1)
		{
			clock_t start=clock();
			topdown(heap,heapsize);
			clock_t end=clock();
			cout<<endl<<end-start<<endl;
		}
	else
		{
			clock_t start=clock();
			bottomup(heap,heapsize);
			clock_t end=clock();
			cout<<endl<<end-start<<endl;
		}

	//for(int i=1;i<=heapsize;i++)
		//cout<<heap[i]<<" ";
	//cout<<endl;

	//heapsort(heap,heapsize);
//for(int i=1;i<=heapsize;i++)
		//cout<<heap[i]<<" ";
	//cout<<endl;

	cout<<endl;
	return 0;
}

