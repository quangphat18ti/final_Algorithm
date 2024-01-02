#pragma once
#include <vector>
#include <algorithm>
using namespace std;

/**
 * Segment Tree without lazy propagation
 *
 * @tparam T type of data
 * @tparam update_function to get parent node from 2 children nodes when update
 * @tparam get_function to get result from two range
 * @tparam n: Range from 0 -> n
 */
template <class T>
class SegmentTree
{
private:
  int n;
  vector<T> nodes;
  T(*update_function)
  (T a, T b);
  T(*get_function)
  (T a, T b);

private:
  void buildTree(int id, int l, int r, const vector<T> &a);
  void update(int id, int l, int r, int i, T val);
  T getRange(int id, int l, int r, int u, int v);

public:
  SegmentTree(T (*update_function)(T, T), T (*get_function)(T, T), int n = 0);
  void resize(int n);
  void clear();

  void buildTree(const vector<T> &a);
  void update(int i, T val);
  T getRange(int u, int v);
};

template <class T>
SegmentTree<T>::SegmentTree(T (*update_function)(T, T), T (*get_function)(T, T), int n)
{
  this->n = n;
  nodes.resize(4 * n + 5);
  this->update_function = update_function;
  this->get_function = get_function;
}

template <class T>
void SegmentTree<T>::resize(int n)
{
  this->n = n;
  nodes.resize(4 * n + 5);
}

template <class T>
void SegmentTree<T>::clear()
{
  n = 0;
  nodes.clear();
}

// build tree from array a
template <class T>
void SegmentTree<T>::buildTree(const vector<T> &a)
{
  vector<T> b = a;
  b.resize(n + 1, 0);
  buildTree(1, 0, n, b);
}

// Update position i with value val
template <class T>
void SegmentTree<T>::update(int i, T val)
{
  if (i < 0 || i > n)
    return;

  update(1, 0, n, i, val);
}

// Get result in range [u, v]
template <class T>
T SegmentTree<T>::getRange(int u, int v)
{
  return getRange(1, 0, n, u, v);
}

template <class T>
void SegmentTree<T>::buildTree(int id, int l, int r, const vector<T> &a)
{
  if (l == r)
  {
    nodes[id] = a[l];
    return;
  }

  int mid = (l + r) / 2;
  buildTree(id << 1, l, mid, a);
  buildTree(id << 1 | 1, mid + 1, r, a);
  nodes[id] = update_function(nodes[id * 2], nodes[id * 2 + 1]);
}

template <class T>
void SegmentTree<T>::update(int id, int l, int r, int i, T val)
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
  nodes[id] = update_function(nodes[id * 2], nodes[id * 2 + 1]);
}

template <class T>
T SegmentTree<T>::getRange(int id, int l, int r, int u, int v)
{
  if (v < l || u > r)
    return 0;

  if (u <= l && r <= v)
    return nodes[id];

  int mid = (l + r) / 2;
  T left = getRange(id << 1, l, mid, u, v);
  T right = getRange(id << 1 | 1, mid + 1, r, u, v);
  return get_function(left, right);
}
