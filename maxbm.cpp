#include "graph.cpp"
using namespace std;
int M,N,E;
bool bpm(Graph &g,int u,bool visited[], int match[])
{
	for(pair<int,int> p:g.adj[u])
	{
		int v = p.first;
		if(!visited[v])
		{
			visited[v]=true;
			if(match[v]==-1 || bpm(g,match[v],visited,match))
			{
				match[v] = u;//job v assigned to applicant u
				return true;
			}
		}
	}
	return false;
}
int bipartiteMatch(Graph &g)
{
	int match[N];//which job(index) was assigned to which applicant
	memset(match,-1,sizeof(match));
	int result = 0;
	for(int i=0;i<M;i++)
	{
		bool visited[N];//mark all jobs as unvisted for each applicant
		memset(visited,false,sizeof(visited));
		if(bpm(g,i,visited,match))
			result++;
	}
	for(int i=0;i<N;i++)
		cout<<"applicant: "<<match[i]<<" -> job: "<<i<<endl;
	return result;
}
int main()
{
	cin>>M>>N;
	cin>>E;
	Graph g(max(M,N),E);
	g.initBipartiteGraph();
	int res = bipartiteMatch(g);
	cout<<"Maximum number of bipartite matchings possible are: "<<res<<endl;
}