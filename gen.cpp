#include <algorithm>
#include <cmath>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
using namespace std;
constexpr bool verboseOutput = false;
constexpr bool printGraph = true;
const int maxTries = 10; // if the code keeps reaching line 182, increase this value

/*
    Compiling:
    g++ -std=c++17 gen.cpp -o gen

    Running:
    ./gen > input_file

    To take input into your code running any algorithm:
    ./boruvka < input_file
*/

const int numVertices = 100;
const bool weighted = true; // change to true, if you want a weighted graph
const int maxweight = 30;
const int START = 0; // for one based indexing graphs

using LL = long long;
using VI = std::vector<int>;

struct DSU {
  VI par;
  VI sizes;
  VI edges;

  int n;

  DSU(int vertices)
    :par { VI(vertices) },
     sizes { VI(vertices, 1) },
     edges { VI(vertices, 0) },
     n { vertices }
  {
    for (int i = 0; i < n; ++i)
      par[i] = i;
  }

  int find(int x) {
    while (x != par[x])
      x = par[x] = par[par[x]];
    return x;
  }

  bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (sizes[x] < sizes[y])
      std::swap(x, y);
    edges[x] += 1;
    if (x == y)
      return false;
    par[y] = x;
    sizes[x] += sizes[y];
    edges[x] += edges[y];
    return true;
  }
};
std::mt19937_64 src((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
template <class T>
T generate(T lower, T upper) {
    return uniform_int_distribution<T>(lower, upper)(src);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  LL m;

  n = numVertices;
  m = generate<int>(n-1, n * (n - 1)/2);

  assert(m >= n - 1);
  assert(m <= n * (n - 1LL) / 2);

  auto succRate = [&](int s) -> long double {
    LL relEdges = n * (n - 1LL) / 2 + n * LL(s - n);
    return  lgammal(s-1) + lgammal(relEdges - m + 1)
      - logl(s) - lgammal(s - n + 1) - lgammal(relEdges + 1);
  };

  int s = n;
  while (succRate(s+1) > succRate(s))
    ++s;

  // mt19937 src { seed };
  using UI = uniform_int_distribution<int>;
  UI rvertex { 0, s - 1 };

  if (verboseOutput)
    cout << "s = " << s << endl;

  for (int currTry = 1; currTry <= maxTries; ++currTry) {
    if (verboseOutput)
      cout << "try #" << currTry << endl;
    DSU dsu { s };
    vector<VI> adj = vector<VI>(s);
    auto tryInsEdge = [&]() -> void {
      int x = rvertex(src);
      int y = rvertex(src);
      if (x == y)
        return;
      bool edgeExists = false;
      for (int z : adj[x])
        if (y == z)
          edgeExists = true;
      if (edgeExists)
        return;
      adj[x].push_back(y);
      adj[y].push_back(x);
      dsu.unite(x, y);
    };

    int root = dsu.find(0);
    while (dsu.sizes[root] <= n && dsu.edges[root] < m) {
      tryInsEdge();
      root = dsu.find(0);
    }
    if (dsu.sizes[root] != n || dsu.edges[root] != m)
      continue;

    struct Edge {
      int x;
      int y;
    };
    vector<int> ps;
    ps.reserve(n);
    vector<Edge> es;
    es.reserve(m);
    for (int i = 0; i < s; ++i)
      if (dsu.find(i) == root) {
        ps.push_back(i);
        for (int j : adj[i])
          if (j > i)
            es.push_back(Edge { i, j });
      }

    assert(int(ps.size()) == n);
    assert(int(es.size()) == m);

    shuffle(es.begin(), es.end(), src);
    // originally there was some edge-removal stuff as well,
    // but it doesn't seem actually useful, so it's commented out
    //es.resize(m);
    auto compress = [&](int p) -> int {
      return int(lower_bound(ps.begin(), ps.end(), p) - ps.begin());
    };

    //dsu = DSU(n);
    for (Edge& e : es) {
      e.x = compress(e.x);
      e.y = compress(e.y);
      //dsu.unite(e.x, e.y);
    }
    //if (dsu.sizes[dsu.find(0)] == n)
    {
      if (printGraph) {
        cout << n << ' ' << m << '\n';
        for (Edge e : es)
          if (weighted)
            cout << e.x + START << ' ' << e.y + START << ' ' << generate<int>(1, maxweight) << '\n';
          else
            cout << e.x + START << ' ' << e.y + START << '\n';
      }
    }

    return 0;
  }

  cerr << "max tries exceeded\n";

  return 1;
}
