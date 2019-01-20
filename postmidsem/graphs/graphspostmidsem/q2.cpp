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
    node * *arr;
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
        temp->arr[i]=NULL;

    return temp;
}

void addedge(list * graph, int u, int v)
{
    node * temp=graph->arr[u];
    node * newn=createnode(v);

    if(temp==NULL)
    {
            graph->arr[u]=newn;
    }
    else
    {
        graph->arr[u]=newn;
        newn->next=temp;
    }
}

void DFS_Visit(list * graph, int u, char * colour, int * parent, int * d,int * f,int &timee)
{
    stack<int> st;
    st.push(u);
    timee+=1;
    d[u]=timee;
    colour[u]='G';

    while(st.empty()==0)
    {
        u=st.top();
        node * temp=graph->arr[u];

        while(temp!=NULL)
        {
            int v=temp->vertex;
            if(colour[v]=='W')
            {
                st.push(v);
                colour[v]='G';
                parent[v]=u;
                cout<<"("<<(char)(u+'q')<<","<<(char)(v+'q')<<"), ";
                timee+=1;
                d[v]=timee;
                break;
            }
            temp=temp->next;
        }

        if(temp==NULL)
        {
            int t=st.top();
            st.pop();
            colour[t]='B';
            timee+=1;
            f[t]=timee;
        }
    }
}

void DFS(list * graph)
{
    int n=graph->size;
    char *colour=new char[n];
    int *parent=new int[n];
    int *d=new int[n];
    int *f=new int[n];

    for(int i=0;i<n;i++)
    {
        colour[i]='W';
        parent[i]=-1;
        d[i]=0;
        f[i]=0;
    }
    int timee=0;
    for(int i=0;i<n;i++)
    {
        if(colour[i]=='W')
            DFS_Visit(graph,i,colour,parent,d,f,timee);
    }

}

int main()
{

    int n,e;
    cin>>n>>e;
    list* graph=createlist(n);
    char v1,v2;
    for(int i=0;i<e;i++)
    {
        cin>>v1>>v2;
        addedge(graph,(int)(v1-'q'),(int)(v2-'q'));
    }
    DFS(graph);

    return 0;
}
