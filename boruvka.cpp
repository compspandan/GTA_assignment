#include "graph.cpp"
vector<pair<int,pair<int,int>>> edges;
struct components
{
	int parent;
	int rank;
};
void inputEdges(int E)
{
	for(int i=0;i<E;i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		edges.push_back({w,{u,v}});
	}
}
int findComp(components c[],int u,int comps)
{
	while(c[u].parent != u)
		u = c[u].parent;
	return u;
}
void uniteComps(components c[],int comp1, int comp2)
{
	if(c[comp1].rank < c[comp2].rank)
		c[comp1].parent = comp2;
	else if(c[comp2].rank < c[comp1].rank)
		c[comp2].parent = comp1;
	else
	{
		c[comp2].parent = comp1;
		c[comp1].rank++;
	}
}
int main()
{
	int N,E;
	cin>>N;
	cin>>E;
	Graph g(N,E);
	inputEdges(E);
	components *c = new components[N];
	int comps=N;
	int *cheapestEdge = new int[N];
	memset(cheapestEdge,-1,sizeof(cheapestEdge));
	for(int i=0;i<N;i++)
	{
		c[i].parent=i;
		c[i].rank=0;
	}
	while(comps>1)
	{
		for (int v = 0; v < comps; ++v)
			cheapestEdge[v] = -1;
		for(int i=0;i<edges.size();i++)
		{
			auto p = edges[i];
			int u=p.second.first,v=p.second.second,w=p.first;
			int comp1 = findComp(c,u,comps);
			int comp2 = findComp(c,v,comps);
			if(comp1==comp2)
				continue;
			if(cheapestEdge[comp1]==-1 || edges[cheapestEdge[comp1]].first > w)
				cheapestEdge[comp1] = i;
			if(cheapestEdge[comp2]==-1 || edges[cheapestEdge[comp2]].first > w)
				cheapestEdge[comp2] = i;
		}
		for(int i=0;i<comps;i++)
		{
			if(cheapestEdge[i]==-1)
				continue;
			int u = edges[cheapestEdge[i]].second.first;
			int v = edges[cheapestEdge[i]].second.second;
			int w = edges[cheapestEdge[i]].first;
			int comp1 = findComp(c,u,comps);
			int comp2 = findComp(c,v,comps);
			if(comp1==comp2)
				continue;
			g.addEdge(u,v,w);
			uniteComps(c,comp1,comp2);
			comps--;
		}
	}
	g.display();
}