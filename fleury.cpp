#include "graph.cpp"
using namespace std;
int main()
{
	int N,E;
	cin>>N;
	cin>>E;
	Graph g(N,E);
	g.initGraph();
	g.display();
}