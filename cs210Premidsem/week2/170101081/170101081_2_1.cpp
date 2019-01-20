#include<iostream>
#include<iomanip> //iomanip is added to use setw to align output one below other (formatting output)
using namespace std;

//function to calculate stockspan of everyday
void stockspansolve(int X[], int S[], int n)
{

	for(int i=0;i<n;i++)
	{
		int temp=X[i],count=1;
		//to calculate how many consective days before the value has been smaller than the current value
		for(int j=i-1;j>=0;j--)
		{
			if(X[j]<=temp)
				count++;
			else
				break; //exit loop as soon as value gets bigger
		}
		S[i]=count;
	}
}

//function to print the output
void print(int X[], int S[], int n)
{
	cout<<"Day    Price    Span"<<endl;

	for(int i=0;i<n;i++)
	{
		cout<<setw(3)<<i<<setw(9)<<X[i]<<setw(8)<<S[i]<<endl; //if iomanip library is not present in the compiler testing the program, remove setw and insert spaces
	}
}

int main()
{
	//taking input
	int n;
	cin>>n;
	int *X=new int[n]; //X stores sock value
	int *S=new int[n]; //S stores the answer

	for(int i=0;i<n;i++)
	{
		cin>>X[i];
	}	
	//calling function to generate answer and print
	stockspansolve(X,S,n);
	print(X,S,n);
	
	//deleting the excess memory created
	delete []X;
	delete []S;

	return 0;
}
