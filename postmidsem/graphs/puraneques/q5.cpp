#include <iostream>
#include<stack>
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
    node * temp=new node;
    temp->vertex=v;
    temp->next=NULL;
    return temp;
}

list * createlist(int n)
{
    list * temp=new list;
    temp->size=n;
    temp->arr= new node *[n];

    for(int i=0;i<n;i++)
        temp->arr[i]=NULL;
    return temp;
}

void addedge(list * graph, int u, int v)
{
    node * temp=graph->arr[u];
    node * newn=createnode(v);
    graph->arr[u]=newn;
    newn->next=temp;
}
stack<int> st;
void stDFS_visit(list * graph, int u,char * colour)
{
    colour[u]='G';
    node * temp=graph->arr[u];
    while(temp!=NULL)
    {
        int v=temp->vertex;
        if(colour[v]=='W')
        {
            stDFS_visit(graph,v,colour);
        }
        temp=temp->next;
    }
    st.push(u);
    colour[u]='B';
}

void DFS_visit(list * graph, int u,char * colour)
{
    cout<<u<<" ";
    colour[u]='G';
    node * temp=graph->arr[u];
    while(temp!=NULL)
    {
        int v=temp->vertex;
        if(colour[v]=='W')
        {
            DFS_visit(graph,v,colour);
        }
        temp=temp->next;
    }
    colour[u]='B';
}
void stDFS(list * graph, char * colour)
{
    int n=graph->size;
    for(int i=0;i<n;i++)
    {
        if(colour[i]=='W')
            stDFS_visit(graph,i,colour);
    }
}

int main()
{
    int n,e;
    cin>>n>>e;
    list *graph1=createlist(n);
    list *graph2=createlist(n);
    for(int i=0;i<e;i++)
    {
        int v1,v2;
        cin>>v1>>v2;
        addedge(graph1,v1,v2);
        addedge(graph2,v2,v1);
    }
    char* colour=new char[n];

    for(int i=0;i<n;i++)
    {
        colour[i]='W';
    }

    stDFS(graph1,colour);

    for(int i=0;i<n;i++)
    {
        colour[i]='W';
    }
    cout<<"Groups:\n";

    while(!st.empty())
    {
        int u=st.top();
        st.pop();
        if(colour[u]=='W')
          {
              DFS_visit(graph2,u,colour);
                cout<<endl;
          }
    }
    return 0;
}
