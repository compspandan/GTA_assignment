// class for undirected graph

#include<bits/stdc++.h>
using namespace std;
class Graph
{
	public:
	int N;//no of vertices
	int E;//no of edges
	vector<pair<int,int>> *adj;
	Graph(int N,int E)
	{
		this->N = N;
		this->E = E;
		adj = new vector<pair<int,int>>[N];
	}
	void initGraph()
	{
		for(int i=0;i<E;i++)
		{
			int u,v,w;
			cin>>u>>v>>w;
			addEdge(u,v,w);
		}
	}
	void addEdge(int u,int v,int w)
	{
		adj[u].push_back({v,w});
		adj[v].push_back({u,w});
	}
	int removeEdge(int u,int v)//returns weight of deleted edge
	{
		int w=1;//default weight
		for(auto itr=adj[u].begin();itr!=adj[u].end();itr++)
			if(itr->first==v)
			{
				w=itr->second;
				adj[u].erase(itr);
				break;
			}
		for(auto itr=adj[v].begin();itr!=adj[v].end();itr++)
			if(itr->first==u)
			{
				w=itr->second;
				adj[v].erase(itr);
				break;
			}
		return w;
	}
	void display()
	{
		for(int i=0;i<N;i++)
		{
			cout<<i<<':';
			for(int j=0;j<adj[i].size();j++)
				cout<<'('<<adj[i][j].first<<','<<adj[i][j].second<<')'<<' ';
			cout<<endl;
		}
	}
	void DFS(int u,bool visited[])
{
	visited[u]=true;
	for(pair<int,int> p:adj[u])
	{
		if(!visited[p.first])
			DFS(p.first,visited);
	}
}
};