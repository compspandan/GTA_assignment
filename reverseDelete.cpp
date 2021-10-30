#include "graph.cpp"
vector<pair<int,pair<int,int>>> edges;
void sortEdges(Graph &g)
{
	for(int i=0;i<g.N;i++)
	{
		for(pair<int,int> p:g.adj[i])
		{
			int w = p.second,u=i,v=p.first;
			edges.push_back({w,{u,v}});
		}
	}
	sort(edges.begin(),edges.end());
	// for(auto p:edges)
	// {
	// 	cout<<p.first<<' '<<p.second.first<<' '<<p.second.second<<endl;
	// }
}
bool isGraphDisconnected(Graph &g)
{
	bool visited[g.N];
	memset(visited,false,sizeof(visited));
	g.DFS(0,visited);
	int count1 = count(visited,visited+g.N,true);
	return (count1==g.N)?false:true;
}
int main()
{
	int N,E;
	cin>>N;
	cin>>E;
	Graph g(N,E);
	g.initGraph();
	sortEdges(g);
	for(int i=edges.size()-1;i>=0;i--)
	{
		int w = edges[i].first;
		int u = edges[i].second.first;
		int v = edges[i].second.second;
		g.removeEdge(u,v);
		if(isGraphDisconnected(g))
			g.addEdge(u,v,w);
	}
	g.display();
}