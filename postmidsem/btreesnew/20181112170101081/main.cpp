#include<bits/stdc++.h>
using namespace std;


int main()
{
	
	int m;
	cin>>m;
	int t=(m+1)/2;
	int min=t-1;
	int n;
	cin>>n;

	int nodeid[n+1],parentid[n+1],nkey[n+1],nchild[n+1],depth[n+1];

	depth[0]=-1;

	for(int i=1;i<=n;i++)
	{
		cin>>nodeid[i]>>parentid[i]>>nkey[i]>>nchild[i];
		depth[nodeid[i]]=depth[parentid[i]]+1;
	}

	for(int i=1;i<=n;i++)
	{
		if(parentid[i]!=0 && nkey[i]<min)
				{
					cout<<"Answer: This cannot be a valid B tree.\nReason: ";
					cout<<nodeid[i]<<" does not have minimum occupancy."<<endl;
					return 0;
				}

		if(nchild[i]!=0 && (nkey[i]+1)!=nchild[i])
			{
				cout<<"Answer: This cannot be a valid B tree.\nReason: ";
				cout<<nodeid[i]<<" does not satisfy the requirement that Children count=Key count + 1."<<endl;
				return 0;
			}
		
	}

	int level=0,nn=-1,count=0;

	for(int i=1;i<=n;i++)
	{
		if(nchild[i]==0)
		{
			if(count==0)
			{
				nn=nodeid[i];
				level=depth[nn];
				count++;
			}
			else
			{
				if(depth[nodeid[i]]!=level)
					{
						cout<<"Answer: This cannot be a valid B tree.\nReason: ";
						cout<<nn<<" and "<<nodeid[i]<<" are a pair of leaf nodes that do not have the same depth."<<endl;
						return 0;
					}					
			}
		}
	}
	cout<<"Answer: This can be a valid B tree."<<endl;

	return 0;
}