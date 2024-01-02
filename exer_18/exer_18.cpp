#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

typedef long long ll;

int n;
vector<int> a;
map<vector<int>, bool> Map;

void nhap()
{
  cin >> n;
  for (int i = 1; i <= n; i++)
  {
    int x;
    cin >> x;
    a.push_back(x);
  }
}

int xuly()
{
  // check if vector is true order, increase from 1 to n
  auto isFinished = [](vector<int> &a) -> bool
  {
    for (int i = 0; i < a.size(); i++)
    {
      if (a[i] != i + 1)
        return false;
    }
    return true;
  };

  Map[a] = true;
  queue<vector<int>> q;
  q.push(a);

  int step = 0;
  int sz = 0;

  while (!q.empty())
  {
    sz = q.size();

    while (sz--)
    {
      vector<int> u = q.front();
      q.pop();

      // cout << "u = ";
      // for (int i = 0; i < u.size(); i++)
      //   cout << u[i] << " ";
      // cout << endl;

      if (isFinished(u))
      {
        cerr << "Num Step: " << step << endl;
        return step;
      }

      for (int i = 1; i < n; i++)
      {
        vector<int> v = u;
        reverse(v.begin(), v.begin() + i + 1);

        // cout << "\tv = ";
        // for (int i = 0; i < v.size(); i++)
        //   cout << v[i] << " ";
        // cout << endl;
        if (Map[v] == false)
        {
          Map[v] = true;
          q.push(v);
        }
      }
    }
    step++;
  }

  return -1;
}

int main()
{
  freopen("exer_18.inp", "r", stdin);
  nhap();
  xuly();
}