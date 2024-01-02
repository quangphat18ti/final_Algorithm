#include <iostream>
#include <vector>
#include <algorithm>

#include "SegmentTree.h"

using namespace std;

typedef long long ll;

int n;
vector<int> a;

void nhap()
{
  cin >> n;
  a.resize(n);
  for (int i = 0; i < n; ++i)
  {
    cin >> a[i];
  }
}

ll count_inverse(vector<int> A)
{
  auto make_pair_value_position = [](const vector<int> &A)
  {
    vector<pair<int, int>> a;
    for (int i = 0; i < A.size(); ++i)
    {
      a.push_back({A[i], i});
    }
    return a;
  };

  vector<pair<int, int>> a = make_pair_value_position(A);
  sort(a.begin(), a.end());

  SegmentTree<int> st(
      [](int a, int b)
      { return a + b; },

      [](int a, int b)
      { return a + b; },

      n);
  st.buildTree(vector<int>(n, 0));

  ll res = 0;
  for (int i = 0; i < a.size(); ++i)
  {
    int j = i;
    while (i < a.size() && a[i].first == a[j].first)
    {
      ++i;
    }
    --i;

    // Range from j to i has the same value
    // We need to count the number of inverse pairs in this range
    for (int k = j; k <= i; ++k)
    {
      // Count the number of elements that are exist from a[k].second + 1 to n -1
      res += st.getRange(a[k].second + 1, n - 1);
    }

    for (int k = j; k <= i; ++k)
    {
      // update exist position: a[k].second
      st.update(a[k].second, 1);
    }
  }

  cerr << res << endl;

  return res;
}
int main()
{
  freopen("exer_4.inp", "r", stdin);
  nhap();
  count_inverse(a);
}