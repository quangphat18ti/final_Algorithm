#pragma once

#include <vector>

using namespace std;

typedef long long ll;

/**
 * Hash build from 1 -> n
 * @brief Hash class
 * @tparam base: base of hash
 * @tparam MOD: mod of hash
 */
class Hash
{
private:
  int base;
  ll MOD;
  vector<ll> hash;
  vector<ll> pow;

public:
  Hash(int base, ll MOD = 1e9 + 7)
  {
    this->base = base;
    this->MOD = MOD;
  }

  void build_hash(const vector<int> &a)
  {
    int n = a.size() - 1;
    hash.resize(n + 1);
    pow.resize(n + 1);

    hash[0] = 0;
    pow[0] = 1;
    for (int i = 1; i <= n; i++)
    {
      hash[i] = (hash[i - 1] * base + a[i]) % MOD;
      pow[i] = (pow[i - 1] * base) % MOD;
    }
  }

  ll get_hash(int l, int r)
  {
    // return (hash[r] - hash[l - 1] * pow[r - l + 1] + MOD * MOD) % MOD;
    return (hash[r] - (hash[l - 1] * pow[r - l + 1] % MOD) + MOD) % MOD;
  }

  ll all()
  {
    return hash.back();
  }
};