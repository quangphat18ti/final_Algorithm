#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;

int n;

vector<int> sangnt(int n)
{
  vector<int> snt(n + 1, 1);
  snt[0] = snt[1] = 0;
  for (int i = 2; i <= sqrt(n); i++)
  {
    if (snt[i])
    {
      for (int j = i * i; j <= n; j += i)
      {
        snt[j] = 0;
      }
    }
  }

  return snt;
}

void solve()
{
  vector<int> snt = sangnt(n * 2);

  auto getPrime = [](const vector<int> &snt)
  {
    vector<int> primes;
    for (int i = 0; i < snt.size(); i++)
    {
      if (snt[i])
      {
        primes.push_back(i);
      }
    }
    return primes;
  };
  vector<int> primes = getPrime(snt);

  ll sum = 0;
  auto getSum = [](vector<int> primes, int n)
  {
    int n2 = n * 2;

    ll sum = 1;                   // for case 2 - 2
    primes.erase(primes.begin()); // remove 2

    int pos_q = primes.size() - 1;
    for (int i = 0; i < primes.size(); i++)
    {
      int p = primes[i];

      if (p > n)
        break;

      int max_q = n2 - p;
      while (pos_q >= i && primes[pos_q] > max_q)
        pos_q--;

      sum += pos_q - i + 1;
    }
    return sum;
  };

  sum = getSum(primes, n);
  cerr << "Sum = " << sum << endl;
  cout << sum << endl;
}

int main()
{
  cerr << "Nhap N = ";
  cin >> n;

  solve();
}