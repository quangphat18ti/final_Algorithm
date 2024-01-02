#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

typedef long long ll;

int n;

void nhap()
{
  cin >> n;
}

/**
 * Use binary to represent the number
 * Exam: bit = 5 -> 101(binary) -> Number: 101 (demical)
 */
unsigned long long solve_binary(int n)
{
  const int MAX_LENGTH = 20;
  auto convert_binary_to_decimal = [](int x) -> unsigned long long
  {
    unsigned long long res = 0;
    for (int i = MAX_LENGTH; i >= 0; i--)
    {
      res = res * 10;
      if (x >> i & 1)
        res++;
    }
    return res;
  };

  for (int i = 1; i < (1 << MAX_LENGTH); i++)
  {
    unsigned long long val = convert_binary_to_decimal(i);

    if (val % n == 0)
    {
      cerr << "value_binary = " << val << endl;
      return val;
    }
  }

  cerr << "value_binary = " << 0 << endl;
  return 0;
}

// No Optimal
string solve_dp(int n)
{
  if (n == 1)
  {
    cerr << "value = 1" << endl;
    return "1";
  }

  const int MAX_LENGTH = 1000000 / n;
  vector<vector<int>> trace(MAX_LENGTH + 1, vector<int>(n, -1));
  vector<vector<bool>> value(MAX_LENGTH + 1, vector<bool>(n, 0));

  vector<int> st1;
  vector<int> st2;

  st1.push_back(1);

  string ans = "-1";

  auto truyvet = [&](int t, int du) -> string
  {
    string res = "";
    while (t > 0)
    {
      res += to_string(value[t][du]);
      du = trace[t][du];
      t--;
    }

    /// t = 0 -> need to add 1
    res += "1";

    reverse(res.begin(), res.end());
    return res;
  };

  for (int t = 1; t <= MAX_LENGTH; t++)
  {
    vector<bool> visited(n, false);

    for (int val : st1)
    {
      int val1 = (val * 10) % n;
      int val2 = (val * 10 + 1) % n;

      if (!visited[val1])
      {
        visited[val1] = true;
        st2.push_back(val1);
        trace[t][val1] = val;
        value[t][val1] = 0;
      }

      if (!visited[val2])
      {
        visited[val2] = true;
        st2.push_back(val2);
        trace[t][val2] = val;
        value[t][val2] = 1;
      }
    }

    if (visited[0])
    {
      ans = truyvet(t, 0);
      cerr << "value = " << ans << endl;
      return ans;
    }

    st1 = st2;
    st2.clear();
  }

  cerr << "value_dp = " << ans << endl;
  return ans;
}

string solve_dp_optimal(int n)
{
  if (n == 1)
  {
    cerr << "value_dp = 1" << endl;
    return "1";
  }

  vector<int> trace(n, -1);
  vector<bool> value(n, 0);

  queue<int> q;
  q.push(1);
  trace[1] = 0;
  value[1] = 1;

  while (!q.empty())
  {
    int top = q.front();
    q.pop();

    int val1 = (top * 10) % n;
    int val2 = (top * 10 + 1) % n;

    if (trace[val1] == -1)
    {
      trace[val1] = top;
      value[val1] = 0;
      q.push(val1);
    }

    if (trace[val2] == -1)
    {
      trace[val2] = top;
      value[val2] = 1;
      q.push(val2);
    }

    if (trace[0] != -1)
    {
      break;
    }
  }

  if (trace[0] == -1)
  {
    cerr << "value_dp = -1" << endl;
    return "-1";
  }

  // Trace back
  string ans = "";
  int temp = 0;
  while (temp != 1)
  {
    ans += to_string(value[temp]);
    temp = trace[temp];
  }
  ans += "1";
  reverse(ans.begin(), ans.end());

  cerr << "value_dp = " << ans << endl;
  return ans;
}
int main()
{
  // freopen("exer_17.inp", "r", stdin);

  // nhap();

  vector<int> diff;
  int start = 100000;
  for (int i = start; i <= 1000000; i++)
  {
    cerr << "n = " << i << endl;

    unsigned long long val = solve_binary(i);
    string ans = solve_dp_optimal(i);
    // convert ull to string
    string val_str = to_string(val);

    if (val == 0)
      continue;

    assert(ans == val_str);
  }

  cerr << "Done!" << endl;
}