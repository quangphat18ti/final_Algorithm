#include <cassert>
#include <iostream>

using namespace std;

#include "SegmentTree.h"

int main()
{
  vector<int> a = {0, 1, 2, 4, 8, 9, 6};
  SegmentTree st(a.size());
  st.buildTree(a);

  int n = 6;

  assert(st.getRange(0, 0) == 0);
  assert(st.getRange(1, 6) == 1);
  assert(st.getRange(2, 4) == 2);
  assert(st.getRange(3, 4) == 4);
  assert(st.getRange(5, 6) == 3);
  cout << "Test Get Range: OK\n";

  st.update(1, 2);
  assert(st.getRange(1, 4) == 2);
  assert(st.getRange(1, 6) == 1);
  st.update(5, 12);
  assert(st.getRange(5, 6) == 6);
  cout << "Test Update: OK\n";
}