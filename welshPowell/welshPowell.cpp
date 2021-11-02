#include "../graph.cpp"
using namespace std;
int color=0;
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
				i--;
			}
		}
		color++;
	}
}
int main()
{
	// freopen("welshPowell.txt", "r", stdin);
	freopen("input.txt", "r", stdin);	
    freopen("welshPowell_output.txt", "w", stdout);
	int N,E;
	cin>>N;
	cin>>E;
	Graph g(N,E);
	g.initGraph();
	vector<pair<int,int>> deg;
	g.findDegree(deg);
	sort(deg.begin(),deg.end(),greater<pair<int,int>>());
	int colors[g.N];
	memset(colors,-1,sizeof(colors));
	welshPowell(g,colors,deg);
	cout<<"Number of colors used: "<<color<<endl;
	for(int i=0;i<g.N;i++)
		cout<<"vertex:"<<i<<"-> color:"<<colors[i]<<endl;
}