#include<iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;

typedef pair<int, pair<int, int> > npair; //declaring pair of pair

//to merge k lists
void merge(int * data, int start, int end, int k, int it) 
{ 
	//it denotes the current value of i in mergebottomup function
    int * buffer=new int[end-start+1]; 
    int bufferindex=0;

    //to store k lists
    vector<vector<int> > karrays(k);
    int temp=0;
    int sizevec=it/k;
    for(int i=start;i<=end;i+=sizevec)
    {	

    	for(int j=i;j<sizevec+i && j<=end;j++)
    		karrays[temp].push_back(data[j]);
    	
    	temp++;

    }
    priority_queue<npair, vector<npair>, greater<npair> > prique; //declaring min priority queue


  	//push first element of each sub list in karrays vector
    for (int i = 0; i < karrays.size(); i++) 
    {
    	if(karrays[i].size()>0)
    	{
    		npair temp1;
    		temp1.first=karrays[i][0];
    		temp1.second.first=i;
    		temp1.second.second=0;
        	
        	prique.push(temp1);
        } 
    }
 
    while(!prique.empty()) 
    { 
    	//extract min element
        npair elem = prique.top(); 
        prique.pop();          
        int i = elem.second.first;   
        int j = elem.second.second;  
  
        buffer[bufferindex++]=elem.first; //store element in buffer
        if (j + 1 < karrays[i].size()) 
            {
            	//push elemnt from same sublist into priority queue
            	npair temp1;
            	temp1.first=karrays[i][j+1];
            	temp1.second.first=i;
            	temp1.second.second=j+1;
            	prique.push(temp1); 
            }
    } 

    //copy back in data
    for(int i=start;i<=end;i++)
    	data[i]=buffer[i-start];

    delete [] buffer;//delete extra buffer

 }
template<class T> void kwaymergesortbottomup(T * data,int n, int k , int val)
{
	int i;
	int temp=0;
	//outer loop for each iteration
	for(i=k;i<n;i*=k)
		{
			if(temp>=val && val!=-1)
				break; //required iterations complete
			for(int start=0;start<n;start+=i)
			{
				if(start<=n-i)
					merge(data,start,start+i-1,k,i);
				else
					merge(data,start,n-1,k,i);
			}
			temp++;

	}
	if(temp<val || val==-1)
	merge(data,0,n-1,k,i);
}
 
int main()
{
	int k,val,n;
	cin>>k>>val>>n;
	int *data=new int[n];
	for(int i=0;i<n;i++)
	cin>>data[i]; 
  	
  	kwaymergesortbottomup(data,n,k,val);
  
  	for(int i=0;i<n;i++)
  		cout<<data[i]<<endl;

  	delete [] data;//delete dynamic input array
    return 0; 
 }