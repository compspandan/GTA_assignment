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
	void removeEdge(int u,int v)
	{
		for(auto itr=adj[u].begin();itr!=adj[u].end();itr++)
			if(itr->first==v)
			{
				adj[u].erase(itr);
				break;
			}
		for(auto itr=adj[v].begin();itr!=adj[v].end();itr++)
			if(itr->first==u)
			{
				adj[v].erase(itr);
				break;
			}	
	}
	void display()
	{
		for(int i=0;i<N;i++)
		{
			cout<<i<<':'<<endl;
			for(int j=0;j<adj[i].size();j++)
				cout<<'('<<adj[i][j].first<<','<<adj[i][j].second<<')'<<' ';
			cout<<endl;
		}
	}
};