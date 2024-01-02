#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

typedef long long ll;

int n;
vector<vector<int>> a;

void nhap()
{
  auto seperate_string_to_vector = [](string s) -> vector<int>
  {
    vector<int> res;
    int i = 0;
    while (i < s.size())
    {
      int j = i;
      while (j < s.size() && s[j] != ' ')
        j++;
      res.push_back(stoi(s.substr(i, j - i)));
      i = j + 1;
    }
    return res;
  };

  cin >> n;

  a.resize(n + 1);

  string s;
  getline(cin, s); // remove \n

  for (int i = 1; i <= n; i++)
  {
    string s;
    getline(cin, s);
    a[i] = seperate_string_to_vector(s);
  }
}

vector<int> solve()
{
  // pair<int,int> = <value, index>
  set<pair<int, int>> st;
  for (int i = 1; i <= n; i++)
  {
    st.insert({a[i][0], i});
  }

  vector<int> ans;

  vector<int> ptr(n + 1, 0);
  while (!st.empty())
  {
    auto it = st.begin();
    int value = it->first;
    int index = it->second;
    st.erase(it);

    ans.push_back(value);

    ptr[index]++;
    if (ptr[index] < a[index].size())
    {
      st.insert({a[index][ptr[index]], index});
    }
  }

  for (int i = 0; i < ans.size(); i++)
  {
    cerr << ans[i] << " ";
  }
  cerr << endl;

  return ans;
}

int main()
{
  freopen("exer_6.inp", "r", stdin);
  nhap();
  solve();
}