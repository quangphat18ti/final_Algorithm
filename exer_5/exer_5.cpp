#include <iostream>
#include <vector>
#include <algorithm>

#include "Hash.h"

using namespace std;

typedef long long ll;

string s;
string t;

void nhap()
{
  // s: 1 -> s.size() - 1
  // t: 1 -> t.size() - 1

  getline(cin, s);
  s = " " + s;

  getline(cin, t);
  t = " " + t;
}

vector<int> solve_Hash(string s, string t)
{
  auto convert_string_to_vector = [](string s)
  {
    auto convert_char_to_int = [](char c)
    {
      if (c >= 'a' && c <= 'z')
      {
        return c - 'a' + 1;
      }
      else
      {
        return c - 'A' + 27;
      }
    };

    int n = s.size();
    vector<int> ans(n);
    for (int i = 1; i < s.size(); i++)
    {
      ans[i] = convert_char_to_int(s[i]);
    }
    return ans;
  };

  vector<int> a = convert_string_to_vector(s);
  vector<int> b = convert_string_to_vector(t);

  Hash hash(61, 1e9 + 7);
  hash.build_hash(a);

  Hash hash2(61, 1e9 + 7);
  hash2.build_hash(b);

  ll val_t = hash2.all();

  int s_size = s.size() - 1;
  int t_size = t.size() - 1;

  vector<int> ans;
  for (int i = 1; i <= s_size; i++)
  {
    if (i + t_size - 1 > s_size)
    {
      break;
    }

    ll val_s = hash.get_hash(i, i + t_size - 1);

    if (val_s == val_t)
    {
      ans.push_back(i);
    }
  }

  cerr << "Hash Algorithm: \n";
  for (int i = 0; i < ans.size(); i++)
  {
    cerr << ans[i] << " ";
  }
  cerr << endl;
  return ans;
}

void solve_KMP(string s, string t)
{
}

void solve_Z_function(string s, string t)
{
}

void solve()
{
  solve_Hash(s, t);
  solve_KMP(s, t);
  solve_Z_function(s, t);
}

int main()
{
  freopen("exer_5.inp", "r", stdin);
  nhap();
  solve();
}