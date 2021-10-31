#include "graph.cpp"
using namespace std;
int color=0;
void findDegree(Graph &g, vector<pair<int,int>> &deg)
{
	for(int i=0;i<g.N;i++)
	{
		int count=0;
		for(pair<int,int> p:g.adj[i])
			count++;
		deg.push_back({count,i});
	}
	sort(deg.begin(),deg.end(),greater<pair<int,int>>());
}
void welshPowell(Graph &g, int colors[], vector<pair<int,int>> deg)
{
	while(deg.size()>0)
	{
		int u = deg.begin()->second;
		if(colors[u]==-1)
		{
			colors[u]=color;
			deg.erase(deg.begin());
		}
		unordered_set<int> neighbour;
		for(pair<int,int> p:g.adj[u])
			neighbour.insert(p.first);
		for(int i=0;i<deg.size();i++)
		{
			auto p = deg[i];
			int v = p.second;
			if(neighbour.find(v)==neighbour.end())//if v is not neighbour of u
			{
				colors[v]=color;
				deg.erase(deg.begin()+i);
			}
		}
		color++;
	}
}
int main()
{
	int N,E;
	cin>>N;
	cin>>E;
	Graph g(N,E);
	g.initGraph();
	vector<pair<int,int>> deg;
	findDegree(g,deg);
	int colors[g.N];
	memset(colors,-1,sizeof(colors));
	welshPowell(g,colors,deg);
	cout<<"Number of colors used: "<<color<<endl;
	for(int i=0;i<g.N;i++)
		cout<<"vertex:"<<i<<"-> color:"<<colors[i]<<endl;
}