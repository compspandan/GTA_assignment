#include "../graph.cpp"
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
void findOddVertices(vector<pair<int,int>> &deg)
{
	for(int i=0;i<deg.size();i++)
	{
		auto p = deg[i];
		if(deg[i].first % 2==0)
		{
			deg.erase(deg.begin()+i);
			i--;
		}
	}
}

void findExactPairs(Graph &g, vector<pair<int,int>> &deg)
{
	vector<pair<int,int>> edge;
	for(int i=0;i<deg.size();i++)
		for(int j=i+1;j<deg.size();j++)
			edge.push_back({deg[i].second,deg[j].second});

	vector<pair<int,int>> pairs;
	for(int i=0;i<edge.size();i++)
	{
		int a = edge[i].first, b = edge[i].second;
		for(int j=i+1;j<edge.size();j++)
		{
			int c = edge[j].first, d = edge[j].second;
			if(c==a || c==b || d==a || d==b)
				continue;
			pairs.push_back({i,j});
		}
	}

	int min = INT_MAX,index=0;
	for(int i=0;i<pairs.size();i++)
	{
		auto p = pairs[i];
		auto e1 = edge[p.first];
		auto e2 = edge[p.second];
		cout<<e1.first<<','<<e1.second<<' '<<e2.first<<','<<e2.second<<endl;
		int sum=0;
		if(g.dp[e1.first][e1.second]==-1)
			g.dikstra(e1.first);
		sum+=g.dp[e1.first][e1.second];

		if(g.dp[e2.first][e2.second]==-1)
			g.dikstra(e2.first);
		sum+=g.dp[e2.first][e2.second];

		if(sum<min)
			index=i;
	}
	if(index!=-1)
	{
		auto p = pairs[index];
		auto e1 = edge[p.first];
		auto e2 = edge[p.second];	
		g.addPath(e1.first,e1.second);
		g.addPath(e2.first,e2.second);
	}
}
int main()
{
	freopen("chinesePM.txt", "r", stdin);
    freopen("chinesePM_output.txt", "w", stdout);
	int N,E;
	cin>>N;
	cin>>E;
	Graph g(N,E);
	g.initGraph();
	vector<pair<int,int>> deg;
	g.findDegree(deg);
	findOddVertices(deg);
	if(deg.size()==0)
	{
		int start = doesEulerPathExist(g);
		if(start!=-1)
			findEulerPath(g,start);
		exit(0);
	}
	findExactPairs(g,deg);
	int start = doesEulerPathExist(g);
		if(start!=-1)
			findEulerPath(g,start);	
		else
			cout<<"No Euler path or circuit exists"<<endl;
}