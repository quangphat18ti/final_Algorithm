// N^2

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int k, n, m;

struct Node
{
  int a, b, index;
};
vector<Node> nodes;

void nhap()
{
  cin >> k >> n >> m;
  nodes.resize(k + 1);

  for (int i = 1; i <= k; i++)
  {
    int a, b;
    cin >> a >> b;
    nodes.push_back({a, b, i});
  }
}

ll xuly()
{
  sort(nodes.begin() + 1, nodes.end(), [](Node x, Node y)
       { return x.b > y.b; });

  // F[i][j] = max value when i node and choose j for A

  vector<vector<ll>> f(k + 1, vector<ll>(n + 1, 0));
  for (int i = 1; i <= k; i++)
  {
    for (int j = 1; j <= n; j++)
    {
      // choose for A
      f[i][j] = max(f[i][j], f[i - 1][j - 1] + nodes[i].a);

      // not choose for A => choose for B
      if (j + m <= i)
      {
        f[i][j] = max(f[i][j], f[i - 1][j] + nodes[i].b);
      }
    }
  }

  cerr << "Max Sum: " << f[k][n] << endl;
  return f[k][n];
}

int main()
{
  freopen("exer_11.inp", "r", stdin);

  nhap();
  xuly();
}