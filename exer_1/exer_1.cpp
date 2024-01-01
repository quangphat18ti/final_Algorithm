/**
## Bài 1: Đoạn con có UCLN lớn nhất

### Tóm tắt:

- Tìm đoạn con đúng k phần tử liên tiếp sao cho UCLN của chúng là MAX.

### Hướng giải:

#### Cách 1: Trâu bò - $O(n \times k)$

- Tại mỗi vị trí, duyệt qua các đoạn con có độ dài k.

#### Cách 2: Sử dụng cấu trúc dữ liệu - $O(nlogk)$

1. Các cấu trúc dữ liệu để tính dãy con liên tiếp. (Segment Tree/ Fenwick Tree/ Sparse Table)

- Độ phức tạp: O(nlogn)

### Mở rộng:

1. Nếu có cập nhật 1 phần tử trong mảng.

- Sử dụng Segment Tree/ Fenwick Tree để cập nhật.

2. Có Q truy vấn, mỗi truy vấn cho mỗi K khác nhau.

- Nếu truy vấn nhiều thì có thể sử dụng RMQ (Range Minimum Query) để giảm độ phức tạp.
*/

#include <iostream>
#include <vector>

#include "SegmentTree.h"

using namespace std;

const int MAXN = 1e5 + 5;

int n, k;
vector<int> a;

struct Query
{
  int type;
  int pos;
  int k;
};
vector<Query> queries;

void nhap();
void nhapVer1();
void nhapVer2();
void ver1(int k);
void ver2(int k, const vector<Query> &queries);

int main()
{
  freopen("exer_1.in", "r", stdin);
  freopen("exer_1.out", "w", stdout);

  nhapVer1();
  ver1(k);

  // nhapVer2();
  // ver2(k, queries);
}

void nhap()
{
  cerr << "Nhap n, k: ";
  cin >> n >> k;
  a.assign(n + 1, 0);
  for (int i = 1; i <= n; ++i)
  {
    cerr << "Nhap a[" << i << "]: ";
    cin >> a[i];
  }
}

void nhapVer1()
{
  nhap();
}

void nhapVer2()
{
  nhap();
  int q;
  cerr << "So luong truy van: ";
  cin >> q;
  queries.resize(q);
  for (int i = 0; i < q; ++i)
  {
    cerr << "Nhap truy van thu " << i + 1 << ": ";
    cin >> queries[i].type >> queries[i].pos >> queries[i].k;
  }
}

// only get, no update
void ver1(int k)
{
  SegmentTree segmentTree(n);
  segmentTree.buildTree(a);

  int ans = -1;
  for (int i = 1; i <= n - k + 1; i++)
  {
    int j = i + k - 1;
    ans = max(ans, segmentTree.getRange(i, j));
  }
  cout << ans << endl;
}

/**
 * Query with 2 types:
 * 1. Update position i with value val
 * 2. Get gcd in range [u, v]
 */
void ver2(int k, const vector<Query> &queries)
{
  SegmentTree segmentTree(n);
  segmentTree.buildTree(a);

  for (int i = 0; i < queries.size(); ++i)
  {
    if (queries[i].type == 1)
    {
      segmentTree.update(queries[i].pos, queries[i].k);
    }
    else
    {
      int u = queries[i].pos;
      int v = queries[i].k;
      cout << segmentTree.getRange(u, v) << endl;
    }
  }
}