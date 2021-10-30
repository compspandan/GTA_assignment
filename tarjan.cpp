#include "graph.cpp"
using namespace std;
int Time = 0;
void DFS(Graph &g, int u, bool visited[], int discTime[], int lowTime[], int par, bool isAP[])
{
    visited[u] = true;
    discTime[u] = ++Time;
	lowTime[u] = Time;
    int childCount = 0;
    for (auto p : g.adj[u]) {
		int v = p.first;
        if (!visited[v]) {
            DFS(g, v, visited, discTime, lowTime, u, isAP);
            childCount++;
            lowTime[u] = min(lowTime[u], lowTime[v]);
            if (par != -1 && lowTime[v] >= discTime[u])
                isAP[u] = true;
        }
        else if (v != par)
            lowTime[u] = min(lowTime[u], discTime[v]);
    }
    if (par == -1 && childCount > 1)
        isAP[u] = true;
}
void findArticulationPoints(Graph &g)
{
	int discTime[g.N];
    int lowTime[g.N];
    bool visited[g.N];
	memset(visited,false,sizeof(visited));
    bool isAP[g.N];
	memset(isAP,false,sizeof(isAP));
	memset(isAP,false,sizeof(isAP));
	int parent = -1;
    for (int i = 0; i < g.N; i++)
        if (!visited[i])
            DFS(g, i, visited, discTime, lowTime, parent, isAP);
	cout<<"Articulation points are: ";
    for (int i = 0; i < g.N; i++)
        if (isAP[i] == true)
            cout << i << " ";
}
int main()
{
	int N,E;
	cin>>N;
	cin>>E;
	Graph g(N,E);
	g.initGraph();
	findArticulationPoints(g);
}