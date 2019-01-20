#include<iostream>
#include<cstdlib>
#include<ctime>
#include<stack>
using namespace std;

template<class Type> void swapE(Type &v1, Type &v2)
{
	Type temp=v1;
	v1=v2;
	v2=temp;
}

template<class Type> void bubblesort(Type *data,int n)
{
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(data[j]>data[j+1])
				swapE(data[j],data[j+1]);
		}
	}
}

template<class Type> void selectionsort(Type *data, int n)
{
	for(int i=0;i<n-1;i++)
	{
		Type small=data[i];
		int index=i;
		for(int j=i+1;j<n;j++)
		{
			if(small>data[j])
			{
				index=j;
				small=data[j];
			}
		}
		if(index!=i)
		{
			swapE(data[i],data[index]);
		}
	}
}

template<class Type> void shiftselectionsort(Type *data, int n)
{
	for(int i=0;i<n-1;i++)
	{
		Type small=data[i];
		int index=i;
		for(int j=i+1;j<n;j++)
		{
			if(small>data[j])
			{
				index=j;
				small=data[j];
			}
		}
		if(index!=i)
		{
			Type temp=data[index];
			for(int j=index-1;j>=i;j--)
			{
				data[j+1]=data[j];
			}
			data[i]=temp;
		}
	}
}

template<class Type> void insertionsort(Type *data, int n)
{
	for(int i=1;i<n;i++)
	{
		Type temp=data[i];
		int j;
		for(j=i-1;temp<data[j];j--)
		{
			data[j+1]=data[j];
		}
		data[j+1]=temp;
	}
}

template<class T> void merge(T * data,int start, int end, int mid)
{
	T buffer[end-start+1];
	int i=start;
	int j=mid+1;
	int k=0;
	while(i<=mid & j<=end)
	{
		if(data[i]<=data[j])
			buffer[k++]=data[i++];
		else
				buffer[k++]=data[j++];

	}

	while(i<=mid)
		buffer[k++]=data[i++];
	while(j<=end)
		buffer[k++]=data[j++];

	for(int i=0;i<end-start+1;i++)
	{
		data[i+start]=buffer[i];
	}
}
template<class T> void mergetopdown(T *data, int start, int end)
{
	if(end-start<1)
		return;
	int mid=(start+end)/2;

	mergesort(data,start,mid);
	mergesort(data,mid+1,end);
    merge(data,start,end,mid);

}


template<class T> void mergesortbottomup(T * data,int n)
{
	int i;
	for(i=2;i<n;i*=2)
		{
			for(int start=0;start<n;start+=i)
			{
				if(start<=n-i)
					merge(data,start,start+i-1,start+i/2-1);
				else
					merge(data,start,n-1,(n+start)/2-1);
			}

	}
	merge(data,0,n-1,i/2-1);
}

template<class T> int partition(T * data, int start, int end)
{
	T pivot=data[start];
	int pos=start;
	for(int i=start+1;i<=end;i++)
		if(data[i]<=pivot)
			pos++;

	swap(data[start],data[pos]);
	int i=start,j=end;
	while(i<pos && j>pos)
	{
		if(data[i]<=pivot)
			i++;
		else
			if(data[j]>pivot)
				j--;
		else
		{
			swap(data[i],data[j]);
			i++;
			j--;
		}
	}
	return pos;
}

template<class T> int partitionNocount(T * data, int start, int end)
{
	T pivot= data[end];

	int i=end;

	for(int j=end-1;j>=start;j--)
	{
		if(data[j]>pivot)
		{
			swap(data[j],data[i]);
			i--;
		}

	}
	return i;
}

template<class T> void quick( T * data, int start, int end)
{
	while(start<end)
    {

	int pos=partitionNocount(data,start,end);
	if(pos-start<end-pos)
    {
        quick(data,start,pos-1);
        start=pos+1;
    }
    else
    {
        quick(data,pos+1,end);
        end=pos-1;
    }
    }

}

template<class T> void norecQuick (T data[], int start, int end)
{
    stack<T> st;

    st.push(start);
    st.push(end);

    while ( !st.empty() )
    {
        end = st.top();
        st.pop();
        start=st.top();
        st.pop();

        int p = partition( data, start, end );

        if ( p-1 > start )
        {
            st.push(start);
            st.push(p-1);
        }

        if ( p+1 < end )
        {
            st.push(p+1);
            st.push(end);
        }
    }
}
int main()
{
	srand(time(0));
	int n;
	cin>>n;
	int * data=new int [n];
	for(int i=0;i<n;i++)
		cin>>data[i];

	for(int i=0;i<n;i++)
		cout<<data[i]<<" ";
	cout<<endl;
	// bubblesort(data, n);
	// for(int i=0;i<n;i++)
	// 	cout<<data[i]<<" ";
	// cout<<endl;

	mergesortbottomup(data,n);
	for(int i=0;i<n;i++)
		cout<<data[i]<<" ";
	cout<<endl;
    //int begin=clock();
    //int end=clock();
    //int tim=((end-begin)/double(CLOCKS_PER_SEC))*1000; //gives time in ms
	return 0;
}
