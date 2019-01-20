#include<iostream>
using namespace std;

int main()
{
	int data;
	cin>>data;

	bool ans=1;
	int max=1000,min=-1;
	bool flag=0;//flag is 0 if prev elemnt is greater
	int n;
	cin>>n;
	while(n!=data)
	{
		if(n>max || n<min)
		{
			ans=0;
		}

		if(n>data && n<max)
		{
			max=n;
		}
		if(n<data && n>min)
		{
			min=n;
		}
		cin>>n;

	}

	if(ans==1)
		cout<<"right"<<endl;
	else
		cout<<"wrong"<<endl;

	return 0;
}