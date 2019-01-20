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
    node * *arr;
};

node * createnode(int v)
{
    node * temp=new node;
    temp->vertex=v;
    temp->next=NULL;
    return temp;
}

list * createlist(int n)
{
    list * temp=new list;
    temp->size=n;
    temp->arr=new node*[n];
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
    graph->arr[u]=newn;

    if(temp!=NULL)
        newn->next=temp;
}

void BFS(list * graph, int u, int **ans, int * parent, int * d)
{
    int n=graph->size;
    char * colour=new char[n];
    for(int i=0;i<n;i++)
        {
            colour[i]='W';
            parent[i]=-1;
            d[i]=100000;
        }
    int t=u;
    queue<int> q;
    q.push(u);
    colour[u]='G';
    d[u]=0;

    while(q.empty()==0)
    {
        u=q.front();
        q.pop();
        node * temp=graph->arr[u];

        while(temp!=NULL)
        {
            int v=temp->vertex;
            if(colour[v]=='W')
            {

                ans[t][v]=1;
                q.push(v);

                colour[v]='G';
                parent[v]=u;
                d[v]=d[u]+1;
            }
            temp=temp->next;
        }
        colour[u]='B';
    }
    delete [] colour;

}
int main()
{
    int n,e;
    cin>>n>>e;
    list* graph=createlist(n);
    int v1,v2;
    for(int i=0;i<e;i++)
    {
        cin>>v1>>v2;
        addedge(graph,v1-1,v2-1);
    }
    int **ans=new int *[n];
    for(int i=0;i<n;i++)
    {
        ans[i]=new int[n];
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        ans[i][j]=0;

    int * parent=new int[n];
    int * d=new int [n];

    for(int i=0;i<n;i++)
    {
        d[i]=100000;
        parent[i]=-1;
    }

    for(int i=0;i<n;i++)
    {
        BFS(graph,i,ans,parent,d);
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            cout<<ans[i][j]<<" ";
        cout<<endl;
    }
    delete []parent;
    delete []d;
    for(int i=0;i<n;i++)
    {
        delete[] ans[i];
    }
    delete[]ans;
    return 0;
}
