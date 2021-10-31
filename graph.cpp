// class for undirected graph

#include<bits/stdc++.h>
using namespace std;
class Graph
{
	public:
	int N;//no of vertices
	int E;//no of edges
	vector<pair<int,int>> *adj;
	int **dp;
	int **parent;
	Graph(int N,int E)
	{
		this->N = N;
		this->E = E;
		adj = new vector<pair<int,int>>[N];
		dp = new int*[N];
		for(int i=0;i<N;i++)
			dp[i]=new int[N];
		memset(dp,-1,sizeof(dp));
		parent = new int*[N];
		for(int i=0;i<N;i++)
			parent[i]=new int[N];
		memset(parent,-1,sizeof(parent));
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

	void recordDist(int dist[], int src)
	{
		for(int i=0;i<N;i++)
		{
			dp[src][i]=dist[i];
			dp[i][src]=dist[i];
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

	void addPath(int src,int dest)
	{
		if (parent[src][dest] == - 1)//if src==dest
			return;
		addPath(src, parent[src][dest]);
		// printf("%d ",dest);
		addEdge(parent[src][dest],dest,dp[parent[src][dest]][dest]);
	}

	void dikstra(int src)
	{
		int dist[N];
		memset(dist,INT_MAX,sizeof(dist));
		dist[src]=0;
		bool sptSet[N];
		memset(sptSet,false,sizeof(sptSet));
		parent[src][src]=-1;
		for (int count = 0; count < N - 1; count++) {
			int u = minDistance(dist, sptSet);
			sptSet[u] = true;
			for (auto p:adj[u])
			{
				int v = p.first,w=p.second;
				if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + w < dist[v])
				{
					parent[src][v] = u;
					dist[v] = dist[u] + w;
				}
			}
		}
		recordDist(dist, src);
	}
};