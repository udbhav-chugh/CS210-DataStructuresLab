#include<iostream>
#include<iomanip> //iomanip is added to use setw to align output one below other (formatting output)
using namespace std;

//declaring node
struct node
{
	int data;
	node* next;
};

//declaring stack
struct stack
{
	node* top;
	int size;
};

//function creates node and returns ints pointer
node* createnode(int d)
{
	node * temp1= new node;
	temp1->data=d;
	temp1->next=NULL;
	return temp1;
}


//this function pushes a newly created node into the stack
void push(stack * s, int d)
{
	node* temp1=createnode(d);
	if(s->top==NULL)
	{
		s->top=temp1;
	}
	else
	{
		temp1->next=s->top;
		s->top=temp1;
	}
	s->size++;

}

//this function removes the topmost elemnt of the stack
//it returns 1 if elemnt is removed and 0 if stack is empty
bool pop(stack *s)
{
	if(s->top==NULL)
	{
		return 0;
	}
	else
	{
		s->size--;
		node* help=s->top;
		s->top=s->top->next;
		delete help;
		return 1;
	}
}

//returns the topmost element of stack and -1 if stack is empty
int topmost(stack *s)
{
	if(s->top==NULL)
		return -1;
	else
		return s->top->data;
}

//returns size of stack
int stSize(stack *s)
{
	return s->size;
}

//function to calculate stockspan of everyday
void stockspansolve(int X[], int S[], stack * st,int n)
{
	//in stack we store the indexes of X[i]s
	//initially we push the first index and assign first day's answer as 1
	S[0]=1;
	push(st,0);

	for(int i=1;i<n;i++)
	{
		
		S[i]=1;//initialise evrydays's output to 1
		
		if(X[i]<topmost(st)) //if value is less than the topmost value on stack i.e. the prev day, answer is 1
		{
			S[i]=1;
			push(st,i);
		}
		else
		{
			
			while(stSize(st)>0 && X[i]>=X[topmost(st)]) //loop runs until stack is empty and value is greater than max topmost element in stack
			{
				S[i]+=S[topmost(st)];
				pop(st);
				
			}
			push(st,i);
		}
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
	//initialising stack
	stack *st=new stack;
	st->top=NULL;
	st->size=0;

	//taking input
	int n;
	cin>>n;

	int *X=new int[n]; //X stores the stock value
	int *S=new int[n]; //S stores the answer

	for(int i=0;i<n;i++)
	{
		cin>>X[i];
	}
	//calling function to generate answer and print
	stockspansolve(X,S,st,n);
	print(X,S,n);
	
	//deleting the excess memory created
	delete []X;
	delete []S;
	delete st;

	return 0;	
}
