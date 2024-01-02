#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 5;

int n;
vector<int> adj[MAXN];

struct Node
{
  ll breadth;
  int nChild;
  ll sumDist;
};
Node nodes[MAXN];

void nhap()
{
  cin >> n;
  for (int i = 1; i < n; i++)
  {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
}

void dfs(int u, int p)
{
  nodes[u].nChild = 1;
  nodes[u].sumDist = 0;
  nodes[u].breadth = 0;

  for (int v : adj[u])
  {
    if (v == p)
      continue;
    dfs(v, u);

    nodes[u].breadth += nodes[v].breadth;
    nodes[u].breadth += nodes[u].nChild * (nodes[v].sumDist + nodes[v].nChild) + nodes[v].nChild * nodes[u].sumDist;

    nodes[u].sumDist += nodes[v].sumDist + nodes[v].nChild;
    nodes[u].nChild += nodes[v].nChild;
  }
}

ll solve()
{
  dfs(1, 0);
  cerr << "nodes[1].breadth = " << nodes[1].breadth << endl;
  return nodes[1].breadth;
}

int main()
{
  freopen("exer_16.inp", "r", stdin);
  nhap();
  solve();
}