#include "SegmentTree.h"

SegmentTree::SegmentTree(int n)
{
  this->n = n;
  nodes.assign(4 * n + 5, 0);
}

void SegmentTree::resize(int n)
{
  this->n = n;
  nodes.assign(4 * n + 5, 0);
}

void SegmentTree::clear()
{
  n = 0;
  nodes.clear();
}

// build tree from array a
void SegmentTree::buildTree(const vector<int> &a)
{
  vector<int> b = a;
  b.resize(n + 1, 0);
  buildTree(1, 1, n, b);
}

// Update position i with value val
void SegmentTree::update(int i, int val)
{
  if (i < 0 || i > n)
    return;

  update(1, 1, n, i, val);
}

// Get gcd in range [u, v]
int SegmentTree::getRange(int u, int v)
{
  return getRange(1, 1, n, u, v);
}

void SegmentTree::buildTree(int id, int l, int r, const vector<int> &a)
{
  if (l == r)
  {
    nodes[id] = a[l];
    return;
  }

  int mid = (l + r) / 2;
  buildTree(id << 1, l, mid, a);
  buildTree(id << 1 | 1, mid + 1, r, a);
  nodes[id] = __gcd(nodes[id * 2], nodes[id * 2 + 1]);
}

void SegmentTree::update(int id, int l, int r, int i, int val)
{
  if (i < l || i > r)
    return;

  if (l == r)
  {
    nodes[id] = val;
    return;
  }

  int mid = (l + r) / 2;
  update(id << 1, l, mid, i, val);
  update(id << 1 | 1, mid + 1, r, i, val);
  nodes[id] = __gcd(nodes[id * 2], nodes[id * 2 + 1]);
}

int SegmentTree::getRange(int id, int l, int r, int u, int v)
{
  if (v < l || u > r)
    return 0;

  if (u <= l && r <= v)
    return nodes[id];

  int mid = (l + r) / 2;
  int left = getRange(id << 1, l, mid, u, v);
  int right = getRange(id << 1 | 1, mid + 1, r, u, v);
  return __gcd(left, right);
}