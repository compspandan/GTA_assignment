#include<bits/stdc++.h>
using namespace std;
class Graph
{
	public:
	int N;
	vector<pair<int,int>> *adj;
	Graph(int N)
	{
		this->N = N;
		adj = new vector<pair<int,int>>(N);
	}
	void initGraph()
	{
		int u,v,w;
		cin>>u>>v>>w;
		adj[u].push_back({v,w});
		adj[v].push_back({u,w});
	}
	void addEdge(int u,int v,int w)
	{
		adj[u].push_back({v,w});
		adj[v].push_back({u,w});
	}
	void removeEdge(int u,int v,int w)
	{
		auto itr = find(adj[u].begin(),adj[u].end(),v);
		adj[u].erase(itr);
		itr = find(adj[v].begin(),adj[v].end(),u);
		adj[v].erase(itr);	
	}
};