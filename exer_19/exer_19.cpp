#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 5;
const ll MAX_VAL = 1e18;

int n;
ll k;
ll a[MAXN];
ll prefix_sum[MAXN];

void nhap()
{
  cin >> n >> k;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
}

ll getSum(int l, int r)
{
  return prefix_sum[r] - prefix_sum[l - 1];
}

void process()
{
  // build Prefix Sum
  prefix_sum[0] = 0;
  for (int i = 1; i <= n; i++)
    prefix_sum[i] = prefix_sum[i - 1] + a[i];
}

vector<int> calc_left(ll X)
{
  vector<int> L(n + 1, 0);
  L[1] = 0;

  for (int i = 2; i <= n; i++)
  {
    L[i] = L[i - 1];
    int j = L[i - 1];
    while (j + 1 < i && a[j + 1] <= X + (i - j - 1))
    {
      j++;
      L[i] = j;
    }
  }
  return L;
}

vector<int> calc_right(ll X)
{
  vector<int> R(n + 1, n + 1);
  R[n] = n + 1;
  for (int i = n - 1; i >= 1; i--)
  {
    R[i] = R[i + 1];
    int j = R[i + 1];
    while (j - 1 > i && a[j - 1] <= X + (j - i - 1))
    {
      j--;
      R[i] = j;
    }
  }
  return R;
}

bool check(ll X)
{
  auto calc_sum = [](ll X, ll dist) -> ll
  {
    // X, X + 1, X + 2, ..., X + dist
    return (X + X + dist) * (dist + 1) / 2;
  };

  vector<int> L = calc_left(X);
  vector<int> R = calc_right(X);

  // cout << "X = " << X << endl;
  // for (int i = 1; i <= n; i++)
  //   cout << L[i] << " ";
  // cout << endl;

  // for (int i = 1; i <= n; i++)
  //   cout << R[i] << " ";
  // cout << endl;

  // from L, R -> check if OK
  for (int i = 1; i <= n; i++)
  {
    // make a[i] = X

    int left = L[i] + 1;
    int right = R[i] - 1;

    if (((unsigned long long)2e18 / abs(X)) < (right - left + 1))
      continue;

    ll sum_left = calc_sum(X, i - left);
    ll sum_right = calc_sum(X, right - i);
    ll sum = sum_left + sum_right - X; // a[i] calc twice

    ll pre_sum = getSum(left, right);

    if (pre_sum - sum <= k)
      return true;
  }

  return false;
}

ll xuly()
{
  ll l = -MAX_VAL;
  ll r = MAX_VAL;
  for (int i = 1; i <= n; i++)
    r = min(r, 1ll * a[i]);
  ll ans = 0;

  while (l <= r)
  {
    ll mid = (l + r) >> 1;
    // cout << "mid = " << mid << ' ' << check(mid) << endl;
    if (check(mid))
    {
      ans = mid;
      r = mid - 1;
    }
    else
      l = mid + 1;
  }

  cerr << "ans = " << ans << endl;
  return ans;
}

int main()
{
  freopen("exer_19.inp", "r", stdin);

  nhap();
  process();
  xuly();
}