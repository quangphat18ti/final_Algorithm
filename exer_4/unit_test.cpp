#include <cassert>
#include <iostream>
#include "SegmentTree.h"

using namespace std;

int main()
{
  cout << endl;
  cout << "Test SegmentTree" << endl;

  int n = 10;
  SegmentTree<int> st(
      [](int a, int b)
      { return a + b; },

      [](int a, int b)
      { return a + b; },

      n);

  vector<int> a(n - 1, 0);
  a[0] = 1;

  st.buildTree(a);
  assert(st.getRange(0, n) == 1);
  assert(st.getRange(0, 0) == 1);
  cout << "Passed Build tree"
       << endl;

  st.update(0, 1);
  st.update(n, 2);

  assert(st.getRange(0, n) == 3);
  assert(st.getRange(0, 0) == 1);
  assert(st.getRange(n, n) == 2);

  st.update(11, 1);
  assert(st.getRange(0, n) == 3);

  cout << "Passed Update"
       << endl;
}