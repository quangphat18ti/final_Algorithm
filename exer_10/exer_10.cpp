#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;

const int MAXN = 1e3 + 5;

int n, m;
int a[MAXN][MAXN];
int sum[MAXN][MAXN];
int f[MAXN][MAXN][2];

void nhap()
{
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= m; j++)
    {
      cin >> a[i][j];
    }
  }
}

void process()
{
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= m; j++)
    {
      sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + a[i][j];
    }
  }
}

int getSquare(int i, int j, bool (*check)(int, int))
{
  int l = 0, r = min(n - i, m - j);
  int res = 0;
  while (l <= r)
  {
    int mid = (l + r) >> 1;
    int x = i + mid, y = j + mid;
    int val = sum[x][y] - sum[x][j - 1] - sum[i - 1][y] + sum[i - 1][j - 1];

    if (check(mid + 1, val))
    {
      res = mid;
      l = mid + 1;
    }
    else
    {
      r = mid - 1;
    }
  }
  return res + 1;
}

int solve_binary_search()
{
  int res = 0;
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= m; j++)
    {

      int square1 = getSquare(i, j, [](int x, int val)
                              { return x * x == val; });

      int square0 = getSquare(i, j, [](int x, int val)
                              { return val == 0; });

      res = max(res, square0);
      res = max(res, square1);
    }
  }

  cerr << "Canh HV: " << res << endl;
  return res;
}

int solve_dp()
{
  int res = 0;
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= m; j++)
    {
      int t = a[i][j];

      f[i][j][t] = min({f[i - 1][j][t], f[i][j - 1][t], f[i - 1][j - 1][t]}) + 1;
      f[i][j][t ^ 1] = 0;
      res = max(res, f[i][j][t]);
    }
  }

  cerr << "Canh HV: " << res << endl;
  return res;
}

// find rectangle with all val
// Nếu làm theo cách DP mà làm theo 2 chiều thì có đúng không?
int solve_rectangle(int val)
{
  auto calc_max_area = [](vector<int> &h) -> int
  {
    vector<int> st;
    h.push_back(0); // sentinel

    int ans = 0;
    for (int i = 0; i < h.size(); i++)
    {
      while (!st.empty() && h[st.back()] >= h[i])
      {
        int height = h[st.back()];
        st.pop_back();

        int width = st.empty() ? i : i - st.back() - 1;
        ans = max(ans, height * width);
      }
      st.push_back(i);
    }

    h.pop_back(); // remove sentinel
    return ans;
  };

  int ans = 0;

  vector<int> h(m + 1, 0);
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= m; j++)
    {
      h[j] = a[i][j] == val ? h[j] + 1 : 0;
    }

    ans = max(ans, calc_max_area(h));
  }

  return ans;
}

int main()
{
  freopen("exer_10.inp", "r", stdin);

  nhap();
  process();

  // solve_binary_search();
  // solve_dp();

  assert(solve_binary_search() == solve_dp());

  cerr << "HCN: " << max(solve_rectangle(0), solve_rectangle(1)) << endl;
}