#include<iostream>
using namespace std;

struct minheap
{
	int key[101];
	int maxheapsize;
	int heapsize;
};

void swap(int &x, int &y)
{
	int temp=x;
	x=y;
	y=temp;
}

void moveup(minheap* h, int i)
{
	int child=i;
	int parent=child/2;

	while(parent>0 && h->key[parent]>h->key[child])
		swap(h->key[parent], h->key[child]);
}

void insert(minheap* h, int k)
{
	h->heapsize++;
	h->key[h->heapsize]=k;
	moveup(h, h->heapsize);
}

int small(minheap* h, int i, int l, int r)
{
	int m=i;
	if(l<=h->heapsize && h->key[l]<h->key[m])
		m=l;
	if(r<=h->heapsize && h->key[r]<h->key[m])
		m=r;
	return m;
}

void heapify(minheap* h, int i)
{
	int l=2*i,r=2*i+1;
	int x=small(h,i,l,r);
	if(x!=i)
	{
		swap(h->key[x],h->key[i]);
		heapify(h,x);
	}
}

void removemin(minheap * h)
{
	swap(h->key[1],h->key[h->heapsize]);
	h->heapsize--;
	heapify(h,1);
}

int getmin(minheap* h)
{
	return h->key[1];
}


int main()
{
	minheap *h=new minheap;
	h->heapsize=0;
	h->maxheapsize=100;
	int n;
	char ans[50];
	int ans1[50];
	int p=0,q=0;
	cin>>n;
	char ch;
	int temp;
	for(int i=1;i<=n;i++)
	{
		cin>>ch;
		if(ch=='i' || ch=='g')
			cin>>temp;

		if(ch=='i')
			{
				insert(h, temp);
				ans[p++]='i';
				ans1[q++]=temp;
			}
		if(ch=='r')
			{
				removemin(h);
				ans[p++]='r';
			}
		if(ch=='g')
		{
			if(temp<getmin(h))
			{
				insert(h,temp);
				ans[p++]='i';
				ans1[q++]=temp;
			}
			else
				if(temp>getmin(h))
				{	
					while(h->heapsize>0 && getmin(h)<temp)
						{
							removemin(h);
							ans[p++]='r';
						}
					if(h->heapsize>0 && getmin(h)>temp)
						{
							insert(h, temp);
							ans[p++]='i';
							ans1[q++]=temp;
						}
					if(h->heapsize==0)
					{

							insert(h, temp);
							ans[p++]='i';
							ans1[q++]=temp;
					}
				}

			ans[p++]='g';
			ans1[q++]=temp;


		}
	}
	int j=0;
	for(int i=0;i<p;i++)
	{
		cout<<ans[i]<<" ";
		if(ans[i]=='i' || ans[i]=='g')
			cout<<ans1[j++];
		cout<<endl;
	}
}