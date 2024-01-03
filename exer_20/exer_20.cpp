#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

typedef long long ll;

int n;
vector<int> a;
ll stt;
vector<ll> factorials;

void nhap()
{
  auto string_int_to_vector = [](string s) -> vector<int>
  {
    vector<int> res;
    stringstream ss(s);
    int x;
    while (ss >> x)
    {
      res.push_back(x);
    }
    return res;
  };

  string s;
  getline(cin, s);

  a = string_int_to_vector(s);

  n = a.size();

  cin >> stt;
}

void process()
{
  // build vector factorial

  factorials.push_back(1);
  for (int i = 1; i <= n; ++i)
  {
    factorials.push_back(factorials[i - 1] * i);
  }
}

// from permutation to number
ll xuly_1(const vector<int> &a)
{
  auto factorial = [](int n) -> ll
  {
    return factorials[n];
  };

  vector<int> b = a;
  sort(b.begin(), b.end());

  ll res = 0;
  for (int i = 0; i < n; ++i)
  {
    int x = a[i];
    int pos = lower_bound(b.begin(), b.end(), x) - b.begin();
    res += pos * factorial(n - i - 1);
    b.erase(b.begin() + pos);
  }

  cerr << "STT = " << res + 1 << endl;
  return res + 1;
}

// from number to permutation
vector<int> xuly_2(ll stt)
{
  auto factorial = [](int n) -> ll
  {
    return factorials[n];
  };

  stt--;
  vector<int> res;
  vector<int> b;
  for (int i = 1; i <= n; ++i)
  {
    b.push_back(i);
  }

  for (int i = 0; i < n; ++i)
  {
    int pos = stt / factorial(n - i - 1);
    res.push_back(b[pos]);
    b.erase(b.begin() + pos);
    stt %= factorial(n - i - 1);
  }

  cerr << "Permutation = ";
  for (int i = 0; i < n; ++i)
  {
    cerr << res[i] << " ";
  }
  cerr << endl;
  return res;
}

int main()
{
  freopen("exer_20.inp", "r", stdin);

  nhap();
  process();
  xuly_1(a);
  xuly_2(stt);
}