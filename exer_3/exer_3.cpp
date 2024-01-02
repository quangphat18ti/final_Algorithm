#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int n, m;
vector<int> a, b;

void nhap()
{
  // cerr << "Nhap n: ";
  cin >> n;
  // cerr << "Nhap m: ";
  cin >> m;
  a.resize(n);
  b.resize(m);
  for (int i = 0; i < n; ++i)
  {
    // cerr << "Nhap a[" << i << "]: ";
    cin >> a[i];
  }
  for (int i = 0; i < m; ++i)
  {
    // cerr << "Nhap b[" << i << "]: ";
    cin >> b[i];
  }
}

/**
 * Chỉ xuất ra giá trị min nhất, chưa truy vết để lưu lại vị trí.
 * Sử dụng 2 con trỏ - Độ phúc tạp O(n + m)
 */
ll xuly(vector<int> a, vector<int> b)
{
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  int ptr_b = b.size() - 1;
  long long minSum = 1e10;

  auto updateSum = [&](int x, int y)
  {
    minSum = min(minSum, abs(1ll * x + y));
  };

  for (int i = 0; i < n; i++)
  {
    int x = a[i];
    while (ptr_b >= 0 && b[ptr_b] > -x)
    {
      ptr_b--;
    }

    if (ptr_b >= 0)
    {
      updateSum(a[i], b[ptr_b]);
    }
    if (ptr_b + 1 < b.size())
    {
      updateSum(a[i], b[ptr_b + 1]);
    }
  }

  cerr << "Ket qua: " << minSum << endl;

  return minSum;
}

/**
 * Sử dụng pair<int,int> để lưu {value, position}
 * Sử dụng 2 con trỏ - Độ phúc tạp O(NlogN)
 *
 * Return pair<int,int> với first là vị trí của a, second là vị trí của b
 */
pair<int, int> xuly_with_position(const vector<int> &A, const vector<int> &B)
{
  // use pair<int,int> to store {value, postion}
  vector<pair<int, int>> a, b;
  auto make_pair_value_position = [](const vector<int> &A)
  {
    vector<pair<int, int>> a;
    for (int i = 0; i < A.size(); ++i)
    {
      a.push_back({A[i], i});
    }
    return a;
  };

  a = make_pair_value_position(A);
  b = make_pair_value_position(B);

  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  long long minSum = 1e10;
  int position_a = -1;
  int position_b = -1;

  int ptr_b = b.size() - 1;
  auto updateSum = [&](int ptr_a, int ptr_b)
  {
    ll temp = abs(1ll * a[ptr_a].first + b[ptr_b].first);
    if (temp < minSum)
    {
      minSum = temp;
      position_a = a[ptr_a].second;
      position_b = b[ptr_b].second;
    }
  };

  for (int i = 0; i < a.size(); ++i)
  {
    int x = a[i].first;
    while (ptr_b >= 0 && b[ptr_b].first > -x)
    {
      ptr_b--;
    }

    if (ptr_b >= 0)
    {
      updateSum(i, ptr_b);
    }
    if (ptr_b + 1 < b.size())
    {
      updateSum(i, ptr_b + 1);
    }
  }

  cerr << "Min Sum: " << minSum << endl;
  cerr << "Vi tri: " << position_a << " " << position_b << endl;

  return make_pair(position_a, position_b);
}

int main()
{
  freopen("exer_3.inp", "r", stdin);
  nhap();
  // xuly(a, b);
  pair<int, int> positon = xuly_with_position(a, b);
  cout << positon.first + 1 << " " << positon.second + 1 << endl;
}