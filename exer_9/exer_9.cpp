#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 1e3 + 5;

int n, m;
string s, t, p;

bool f[MAXN][MAXN];

void nhap()
{
  getline(cin, s);
  getline(cin, t);

  n = s.size();
  m = t.size();

  s = " " + s;
  t = " " + t;
}

void standardize()
{
  // standardize t
  // if t[i] == '*' then p[i] = t[i - 1] and pop t[i - 1]

  string temp = " ";
  p = " ";

  for (int i = 1; i <= m; i++)
  {
    if (i < m && t[i + 1] == '*')
    {
      temp += t[i + 1];
      p += t[i];
      i++;
    }
    else
    {
      temp += t[i];
      p += t[i];
    }
  }

  t = temp;
}

void xuly()
{
  standardize();
  cerr << "s =" << s << endl;
  cerr << "t =" << t << endl;
  cerr << "p =" << p << endl;

  m = t.size() - 1;

  // f[i][j] = true if s[1..i] is a instance of t[1..j]

  for (int i = 1; i <= m; i++)
  {
    f[0][i] = 0;
  }

  for (int i = 0; i <= n; i++)
  {
    f[i][0] = 1;
  }

  f[0][0] = 1;

  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= m; j++)
    {
      if (t[j] == '.')
      {
        f[i][j] = f[i - 1][j - 1];
      }
      else if (t[j] == '*')
      {
        if (p[j] == '.' || s[i] == p[j])
        {
          f[i][j] = f[i - 1][j] || f[i][j - 1] || f[i - 1][j - 1];
        }
        else
        {
          f[i][j] = f[i][j - 1];
        }
      }
      else
      {
        f[i][j] = f[i - 1][j - 1] && (s[i] == t[j]);
      }
    }
  }

  cout << (f[n][m] ? "true" : "false") << endl;
}

// Link: https://leetcode.com/problems/wildcard-matching/description/
bool another_version()
{
  vector<vector<bool>> f(n + 1, vector<bool>(m + 1, false));

  f[0][0] = 1;
  for (int i = 1; i <= m; i++)
  {
    if (p[i] != '*')
      break;
    f[0][i] = 1;
  }

  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= m; j++)
    {
      if (p[j] == '?')
      {
        f[i][j] = f[i - 1][j - 1];
      }
      else if (p[j] == '*')
      {
        f[i][j] = f[i - 1][j] | f[i - 1][j - 1] | f[i][j - 1];
      }
      else
      {
        f[i][j] = f[i - 1][j - 1] & (s[i] == p[j]);
      }
    }
  }

  cout << (f[n][m] ? "true" : "false") << endl;
  return f[n][m];
}

int main()
{
  freopen("exer_9.inp", "r", stdin);
  nhap();
  xuly();
}