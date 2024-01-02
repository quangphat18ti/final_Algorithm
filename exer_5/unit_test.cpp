#include <iostream>
#include <cassert>
#include <vector>

#include "Hash.h"

using namespace std;

typedef long long ll;

int main()
{
  vector<int> a = {0, 1, 2, 3, 2, 3, 3, 3, 3};

  cout << "\n>>> Test Hash <<< " << endl;
  Hash hash(31, 1e9 + 7);
  hash.build_hash(a);

  assert(hash.get_hash(1, 1) == 1);
  assert(hash.get_hash(1, 2) == 33);
  assert(hash.get_hash(2, 3) == hash.get_hash(4, 5));
  assert(hash.get_hash(1, 3) != hash.get_hash(4, 5));
  assert(hash.get_hash(5, 7) == hash.get_hash(6, 8));

  cout << "Test Hash: OK\n"
       << endl;
}