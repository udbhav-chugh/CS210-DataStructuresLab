#include<iostream>
#include<queue>
#include<stack>
#include<climits>
using namespace std;

struct node
{
	int vertex;
	int weight;
	node* next;
};


struct list
{
	int size;
	node ** arr;
};

int timee=0;


list * createlist(int n)
{
	list * glist= new list;
	glist->size=n;
	glist->arr=new node*[n];
	for(int i=0;i<n;i++)
	{
		glist->arr[i]=NULL;
	}

	return glist;
}

node * createnode(int v, int w)
{
	node * temp=new node;
	temp->vertex=v;
	temp->weight=w;
	temp->next=NULL;
	return temp;
}

void addedge(list *glist,int u, int v, int x)
{
	node * newn=createnode(v,x);
	node * temp=glist->arr[u];
	glist->arr[u]=newn;
    newn->next=temp;
}

void print(list *glist)
{
	for(int i=0;i<glist->size;i++)
	{
		cout<<i<<": ";
		node * temp=glist->arr[i];
		while(temp!=NULL)
		{
			cout<<temp->vertex<<"("<<temp->weight<<") ";
			temp=temp->next;
		}
		cout<<endl;
	}
}

void BFS(list * graph, int u, char *colour, int * parent, int * d)
{
	queue<int> q;

	if(colour[u]=='W')
	{
		d[u]=0;
		q.push(u);
		colour[u]='G';
	}

	while(q.empty()==0)
	{
		u=q.front();
		q.pop();
		cout<<u<<" ";
		node * temp=graph->arr[u];

		while(temp!=NULL )
		{
		    int v=temp->vertex;
			if(colour[v]=='W')
			{
				q.push(v);
				colour[v]='G';
				d[v]=d[u]+1;
				parent[v]=u;
			}
			temp=temp->next;
		}
		colour[u]='B';
	}


}

void printpath(list * graph, int *parent, int v)
{
	if(parent[v]==-1)
	{
		cout<<v<<" ";
		return ;
	}
	printpath(graph,parent,parent[v]);
	cout<<v<<" ";
}
void DFSvisit(list * graph,int u, char * colour,int* parent,int* timeini,int* timefin)
{
	cout<<u<<" ";
	colour[u]='G';
	timee+=1;
	timeini[u]=timee;

	node * temp=graph->arr[u];

	while(temp!=NULL)
	{
	    int v=temp->vertex;
		if(colour[v]=='W')
		{
			parent[v]=u;
			DFSvisit(graph,v,colour,parent,timeini,timefin);
		}
		temp=temp->next;
	}

	colour[u]='B';
	timee+=1;
	timefin[u]=timee;
}

void DFS(list * graph,char *colour,int *parent,int * timeini,int * timefin)
{
    int n=graph->size;

	for(int i=0;i<n;i++)
	{
		colour[i]='W';
		parent[i]=-1;
		timeini[i]=0;
		timefin[i]=0;
	}
	for(int i=0;i<n;i++)
	{
		if(colour[i]=='W')
		DFSvisit(graph,i, colour, parent, timeini, timefin);
	}
}
int main()
{
	int n,e;
	cin>>n>>e;
	list *graph =createlist(n);

	int v1,v2,x;

	for(int i=0;i<e;i++)
	{
		cout<<"enter edge and weight: ";
		cin>>v1>>v2>>x;
		addedge(graph,v1,v2,x);
	}

	cout<<endl;
	print(graph);
	cout<<endl;

	char *colour=new char[n];
	int *parent=new int[n];
	int *d=new int[n];

	for(int i=0;i<n;i++)
	{
		colour[i]='W';
		parent[i]=-1;
		d[i]=INT_MAX;
	}

	for(int i=0;i<n;i++)
	{
	    if(colour[i]=='W')
		BFS(graph,i,colour,parent,d);
	}
	cout<<endl;

	printpath(graph,parent,3);

	int *timeini=new int[n];
	int *timefin=new int[n];
	cout<<endl;

    DFS(graph,colour,parent,timeini,timefin);

	delete[] colour;
	delete[] d;
	delete[] parent;
	delete[] timeini;
	delete[] timefin;
}
