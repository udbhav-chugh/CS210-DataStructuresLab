#include<iostream>
#include<vector>
#include<queue>
#include<stack>

using namespace std;



struct Graph{
	int v;
	bool **adj;
	public:
		Graph(int vcount);
		void addEdge(int u,int v);
		void deleteEdge(int u,int v);
		vector<int> BFS(int s);
		vector<int> DFS(int s);
		vector<int> DFSn(int s, vector<bool> & visited);
		void DFSUtil(int s,vector<int> &dfs,vector<bool> &visited);
		void DFScomp(int s,vector<bool> & visited);
		int comp();
		void DFSUtilst(int s, stack<int> &st,vector<bool> &visited);
		void DFSst(Graph * g2);
		void BFSbi(int s,vector<int> &colour,vector<bool> &visited);
		vector<int> BFSbitot();
};

Graph::Graph(int vcount){
	this->v = vcount;
	this->adj=new bool*[vcount];
	for(int i=0;i<vcount;i++)
		this->adj[i]=new bool[vcount];
	for(int i=0;i<vcount;i++)
		for(int j=0;j<vcount;j++)
			adj[i][j]=false;
}

void Graph::addEdge(int u,int w){
	this->adj[u][w]=true;
}

void Graph::deleteEdge(int u,int w){
	this->adj[u][w]=false;
	this->adj[w][u]=false;
}

vector<int> Graph::BFS(int s){
	vector<bool> visited(this->v);
	vector<int> bfs;
	queue<int> que;
	que.push(s);
	visited[s]=true;
	while(!que.empty()){
		bfs.push_back(que.front());
		for(int i=0;i<this->v;i++){
			if(adj[que.front()][i]==true && visited[i]==false){
				visited[i]=true;
				que.push(i);
			}
		}
		que.pop();
	}
	return bfs;
}

void Graph::DFSUtil(int s, vector<int> &dfs, vector<bool> &visited){
	visited[s]=true;
	dfs.push_back(s);
	for(int i=0;i<this->v;i++){
		if(this->adj[s][i]==true && visited[i]==false)
			DFSUtil(i,dfs,visited);
	}
}

vector<int> Graph::DFS(int s){
	vector<bool> visited(this->v);
	vector<int> dfs;
	DFSUtil(s,dfs,visited);
	return dfs;
}
vector<int> Graph::DFSn(int s,vector<bool> &visited){
	vector<int> dfs;
	DFSUtil(s,dfs,visited);
	return dfs;
}

void Graph::DFScomp(int s,vector<bool> & visited)
{
    visited[s]=1;
    for(int i=0;i<v;i++)
    {
        if(adj[s][i]==1 && visited[i]==0)
            DFScomp(i,visited);
    }
}

int Graph:: comp()
{
    vector<bool> visited(v);
    int ans=0;
    for(int i=0;i<v;i++)
    {
        if(visited[i]==0)
        {
            DFScomp(i,visited);
            ans++;
        }
    }
    return ans;
}

void Graph::DFSUtilst(int s, stack<int> &st, vector<bool> &visited)
{
    visited[s]=1;
    for(int i=0;i<v;i++)
    {
        if(adj[s][i]==1 && visited[i]==0)
            DFSUtilst(i,st,visited);
    }
    st.push(s);
}

void Graph::DFSst(Graph * g2)
{
    stack<int> st;
    vector<bool> visited(v);

    for(int i=0;i<v;i++)
    {
        if(visited[i]==0)
            DFSUtilst(i,st,visited);
    }
    for(int i=0;i<v;i++)
        visited[i]=0;

    while(st.empty()==0)
    {
        int s=st.top();
        st.pop();
        if(visited[s]==0)
        {
            vector<int> temp=g2->DFSn(s,visited);
            for(int i=0;i<temp.size();i++)
                cout<<temp[i]<<" ";
            cout<<endl;
        }
    }
}

void Graph::BFSbi(int s,vector<int> &colour,vector<bool> &visited)
{
	vector<int> d(v);
	queue<int> q;
	visited[s]=1;
	q.push(s);
	d[s]=0;
	colour[s]=1;

	while(q.empty()==0)
	{
		s=q.front();
		for(int i=0;i<v;i++)
		{
			if(adj[s][i]==1 && visited[i]==0)
			{
				q.push(i);
				d[i]=d[s]+1;
				visited[i]=1;
				if(d[i]%2)
					colour[i]=0;
				else
					colour[i]=1;
			}
		}
		q.pop();

	}
}

vector<int> Graph::BFSbitot()
{
	vector<int> colour(v);
	vector<bool> visited(v);
	for(int i=0;i<v;i++)
	{
		if(visited[i]==0)
			BFSbi(i,colour,visited);
	}
	return colour;
}
