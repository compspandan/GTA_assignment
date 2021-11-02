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
	void initBipartiteGraph()
	{
		for(int i=0;i<E;i++)
		{
			int u,v,w;
			cin>>u>>v>>w;
			adj[u].push_back({v,w});
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
	void findDegree(vector<pair<int,int>> &deg)
	{
		for(int i=0;i<N;i++)
		{
			int count=0;
			for(pair<int,int> p:adj[i])
				count++;
			deg.push_back({count,i});
		}
	}

	int minDistance(int dist[], bool sptSet[])
	{
		int min = INT_MAX, min_index;
		for (int v = 0; v < N; v++)
			if (sptSet[v] == false && dist[v] <= min)
				min = dist[v], min_index = v;
		return min_index;
	}

	void addPathEdges(int dest,int dist[],int parent[])
	{
		if (parent[dest] == - 1)//if src==dest
		{
			return;
		}
		addPathEdges(parent[dest],dist,parent);
		int w = abs(dist[parent[dest]] - dist[dest]);
		cout<<"adding edge"<<parent[dest]<<"->"<<dest<<" weight:"<<w<<endl;
		addEdge(parent[dest],dest,w);
	}

	int dikstra(int src,int dest,bool addPath=false)
	{
		int dist[N];
		bool sptSet[N];
		int parent[N];
		for(int i=0;i<N;i++)
		{
			dist[i]=INT_MAX;
			sptSet[i] = false;
			parent[i]=-1;
		}
		dist[src]=0;
		parent[src]=-1;
		for (int count = 0; count < N - 1; count++) {
			int u = minDistance(dist, sptSet);
			sptSet[u] = true;
			if(u==dest)
				break;
			for (auto p:adj[u])
			{
				int v = p.first,w=p.second;
				// cout<<sptSet[v]<<' '<<dist[u]<<' '<<dist[v]<<endl;
				if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + w < dist[v])
				{
					parent[v] = u;
					dist[v] = dist[u] + w;
				}
			}
		}
		if(addPath)
		{
			// cout<<src<<' '<<dest<<endl;
			addPathEdges(dest,dist,parent);
		}
		return dist[dest];
	}
};