#include "graph.cpp"
using namespace std;
int doesEulerPathExist(Graph &g)
{
	int count = 0, u;
	for(int i=0;i<g.N;i++)
	{
		if(g.adj[i].size() & 1)//count number of odd degree vertices
		{
			count++;
			u=i;
		}
	}
	if(count==0)
		return 0;
	else if(count==2)
		return u;
	else
		return -1;
}

// 
bool isEdgeValid(Graph &g,int u,int v)
{
	if(g.adj[u].size()==1)
		return true;
	bool visited[g.N];
	memset(visited,false,sizeof(visited));
	g.DFS(u,visited);
	int count1 = count(visited,visited+g.N,true);
	int w = g.removeEdge(u,v);
	memset(visited,false,sizeof(visited));
	g.DFS(u,visited);
	int count2 = count(visited,visited+g.N,true);
	g.addEdge(u,v,w);
	return (count2<count1)?false:true;
}
void findEulerPath(Graph &g, int u)
{
	for(int i=0;i<g.adj[u].size();i++)
	{
		pair<int,int> p = g.adj[u][i];
		int v = p.first;
		if(isEdgeValid(g,u,v))
		{
			cout<<u<<"-"<<v<<endl;
			g.removeEdge(u,v);
			findEulerPath(g,v);
		}
	}
}
int main()
{
	int N,E;
	cin>>N;
	cin>>E;
	Graph g(N,E);
	g.initGraph();
	int start = doesEulerPathExist(g);
	if(start!=-1)
		findEulerPath(g,start);
	else
		cout<<"No Euler path or circuit exists"<<endl;
}