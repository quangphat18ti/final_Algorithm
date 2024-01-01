#pragma once
#include <vector>
#include <algorithm>
using namespace std;

class SegmentTree
{
private:
  vector<int> nodes;
  int n;

private:
  void buildTree(int id, int l, int r, const vector<int> &a);
  void update(int id, int l, int r, int i, int val);
  int getRange(int id, int l, int r, int u, int v);

public:
  SegmentTree(int n = 0);
  void resize(int n);
  void clear();

  void buildTree(const vector<int> &a);
  void update(int i, int val);
  int getRange(int u, int v);
};