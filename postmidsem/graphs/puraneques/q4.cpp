#include <iostream>
#include<queue>
using namespace std;

struct node
{
    int vertex;
    node * next;
};

struct list
{
    int size;
    node* *arr;
};

node * createnode(int v)
{
    node * temp= new node;
    temp->vertex=v;
    temp->next=NULL;
    return temp;
}

list * createlist(int n)
{
    list * temp=new list;
    temp->size=n;
    temp->arr=new node *[n];
    for(int i=0;i<n;i++)
    {
        temp->arr[i]=NULL;
    }
    return temp;
}

void addedge(list * graph, int u, int v)
{
    node * temp=graph->arr[u];
    node * newn=createnode(v);

    if(temp==NULL)
        graph->arr[u]=newn;
    else
    {
        graph->arr[u]=newn;
        newn->next=temp;
    }
}

void BFS(list * graph, int u, char *colour, int * parent, int* d, char * group )
{
    queue<int> q;
    q.push(u);
    colour[u]='G';
    d[u]=0;
    group[u]='G';
    int flag=0;

    while(q.empty()==0)
    {
        u=q.front();
        q.pop();
        node * temp=graph->arr[u];
        int count=0;
        while(temp!=NULL)
        {
            int v=temp->vertex;
            if(colour[v]=='W')
            {
                count++;
                q.push(v);
                colour[v]='G';
                d[v]=d[u]+1;

            if(d[v]%2)
                {
                    group[v]='B';
                }
                else
                {
                    group[v]='G';
                }
            }

                temp=temp->next;

        }
        colour[u]='B';

    }
}

int main()
{
    int n,e;
    cin>>n>>e;
    list * graph=createlist(n);

    int v1,v2;
    for(int i=0;i<e;i++)
    {
        cin>>v1>>v2;
        addedge(graph,v1-1,v2-1);
        addedge(graph,v2-1,v1-1);
    }

    char * colour= new char[n];
    char * group = new char[n];
    int * parent= new int[n];
    int * d=new int[n];

    for(int i=0;i<n;i++)
    {
        colour[i]='W';
        group[i]='N';
        parent[i]=-1;
        d[i]=10000;
    }
    int temp;
    for(int i=0;i<n;i++)
    {
        if(colour[i]=='W')
            BFS(graph,i,colour,parent,d,group);
    }

    for(int i=0;i<n;i++)
    {
        node * temp=graph->arr[i];
        char ch=group[i];
        while(temp!=NULL)
        {
            int v=temp->vertex;
            if(group[v]==ch)
            {
                cout<<"Not possible"<<endl;
                return 0;
            }
            temp=temp->next;
        }
    }

    cout<<"GOOD: ";
    for(int i=0;i<n;i++)
    {
        if(group[i]=='G')
        cout<<i+1<<" ";
    }
    cout<<endl;

    cout<<"BAD: ";
    for(int i=0;i<n;i++)
    {
        if(group[i]=='B')
        cout<<i+1<<" ";
    }
    cout<<endl;

    return 0;
}
