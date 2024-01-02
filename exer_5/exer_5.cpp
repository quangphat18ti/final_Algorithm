#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

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

vector<int> solve_KMP(string s, string t)
{
  auto build_prefix_function = [](string s)
  {
    if (s[0] != ' ')
    {
      s = " " + s;
    }

    int n = s.size();
    vector<int> pi(n);
    pi[0] = 0;
    pi[1] = 0;
    for (int i = 2; i < n; i++)
    {
      int j = pi[i - 1];
      while (j > 0 && s[i] != s[j + 1])
      {
        j = pi[j];
      }

      if (s[i] == s[j + 1])
      {
        j++;
      }
      pi[i] = j;
    }
    return pi;
  };

  vector<int> prefix = build_prefix_function(t);

  // cerr << "Prefix function: \n";
  // for (int i = 0; i < prefix.size(); i++)
  // {
  //   cerr << prefix[i] << " ";
  // }
  // cerr << endl;

  int s_size = s.size() - 1;
  int t_size = t.size() - 1;

  vector<int> ans;
  int j = 0;
  for (int i = 1; i <= s_size; i++)
  {
    while (j > 0 && s[i] != t[j + 1])
    {
      j = prefix[j];
    }

    if (s[i] == t[j + 1])
    {
      j++;
    }

    if (j == t_size)
    {
      ans.push_back(i - t_size + 1);
      j = prefix[j];
    }

    // cerr << i << ' ' << j << endl;
  }

  cerr << "KMP Algorithm: \n";
  for (int i = 0; i < ans.size(); i++)
  {
    cerr << ans[i] << " ";
  }
  cerr << endl;

  return ans;
}

vector<int> solve_Z_function(string s, string t)
{
  // s = [1 .. n]
  // Z[i] is the length of the longest substring starting from i which is also a prefix of s
  // Z[i] = k -> s[i..i + k - 1] = s[1..k]
  auto build_Z_function = [](string s)
  {
    cout << s << endl;
    int n = s.size();
    vector<int> Z(n);

    Z[0] = Z[1] = 0;
    int l = 0, r = 0;

    for (int i = 2; i < n; i++)
    {
      if (i <= r)
      {
        // s[i .. r] = s[i - l .. r - l]
        Z[i] = min(r - i + 1, Z[i - l]);
      }

      while (i + Z[i] < n && s[Z[i] + 1] == s[i + Z[i]])
      {
        Z[i]++;
      }

      if (i + Z[i] - 1 > r)
      {
        l = i;
        r = i + Z[i] - 1;
      }
    }

    return Z;
  };

  vector<int> Z = build_Z_function(t + "#" + s);

  vector<int> ans;
  for (int i = 0; i < Z.size(); i++)
  {
    if (Z[i] == t.size() - 1)
    {
      ans.push_back(i - (t.size() + 1));
    }
  }
  cerr << "Z Algorithm: \n";
  for (int i = 0; i < ans.size(); i++)
  {
    cerr << ans[i] << " ";
  }
  cerr << endl;

  return ans;
}

void solve()
{
  vector<int> ans1 = solve_Hash(s, t);
  vector<int> ans2 = solve_KMP(s, t);
  vector<int> ans3 = solve_Z_function(s, t);

  assert(ans1 == ans2);
  assert(ans1 == ans3);

  cerr << "All Algorithm are correct\n";

  for (int i = 0; i < ans1.size(); i++)
  {
    cout << ans1[i] << " ";
  }
  cout << endl;
}

int main()
{
  freopen("exer_5.inp", "r", stdin);
  nhap();
  solve();
}