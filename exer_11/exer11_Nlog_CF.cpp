// Link đề: https://codeforces.com/contest/730/problem/I

/**
 * Nhìn bài toán theo 1 góc nhìn khác:

- Cho $K$ phần tử.

  - Mỗi phần tử sẽ có sức mạnh bình thường là $b_i$.
  - Nếu được nâng cấp sức mạnh thì sẽ đạt được mức là : $a_i$. (Không đảm bảo $a_i > b_i$)

- Bạn được chọn ra $N + M$ phần tử trong tập hợp. Đồng thời buộc phải nâng cấp cho $N$ phần tử trong số đó. Hỏi: Tổng sức mạnh lớn nhất có thể đạt được là bao nhiêu?
  - Nếu nâng cấp thì mình sẽ được: $a_i - b_i$.
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

typedef pair<int, int> pii;

struct Node
{
  int a, b, index;
};
vector<Node> nodes;

int n, m, k;

void nhap();
void nhap_codeforces();

vector<int> find_A(vector<Node> nodes, int n, int m)
{
  vector<pair<int, int>> value_B_index;
  for (int i = 0; i < k; i++)
  {
    value_B_index.push_back({nodes[i].b, nodes[i].index});
  }
  sort(value_B_index.begin(), value_B_index.end(), [](pair<int, int> a, pair<int, int> b)
       { return a.first > b.first; });

  set<pair<int, int>> value;
  set<pair<int, int>> diff_1;
  set<pair<int, int>> diff_2;

  for (int i = 0; i < n + m; i++)
  {
    int index = value_B_index[i].second;
    value.insert({nodes[index].b, nodes[index].index});
    diff_1.insert({-(nodes[index].a - nodes[index].b), nodes[index].index});
    // cout << nodes[index].a << " " << nodes[index].b << ' ' << index << endl;
  }

  for (int i = n + m; i < k; i++)
  {
    int index = value_B_index[i].second;

    diff_2.insert({-nodes[index].a, nodes[index].index});
  }

  vector<int> A;
  for (int i = 0; i < n; i++)
  {
    auto d1_begin = diff_1.begin();
    int tam = d1_begin->second;
    int val = -d1_begin->first;

    auto d2_begin = diff_2.begin();
    int tam2 = d2_begin->second;
    int val2 = -d2_begin->first;

    auto value_begin = value.begin();

    val2 = val2 - value_begin->first;

    if (val2 > val)
    {
      A.push_back(tam2);
      diff_2.erase(d2_begin);

      int index = value_begin->second;
      diff_1.erase({-(nodes[index].a - nodes[index].b), index}); // remove from diff_1
      value.erase(value_begin);                                  // remove from value
      diff_2.insert({-nodes[index].a, index});                   // add to diff_2
    }
    else
    {
      A.push_back(tam);
      // remove index tam from value
      value.erase({nodes[tam].b, tam});
      // remove index tam from diff_1
      diff_1.erase(d1_begin);
    }
  }
  return A;
}

// remove nodes[i] with i in A
vector<Node> find_rest(vector<Node> nodes, const vector<int> &A)
{
  vector<Node> nodes_rest;
  int ptr = 0;
  for (int i = 0; i < nodes.size(); i++)
  {
    if (ptr >= A.size())
    {
      nodes_rest.push_back(nodes[i]);
      continue;
    }

    if (i > A[ptr])
    {
      ptr++;
    }

    if (i != A[ptr])
    {
      nodes_rest.push_back(nodes[i]);
    }
  }

  return nodes_rest;
}

vector<int> find_B(vector<Node> nodes, int n, int m)
{
  sort(nodes.begin(), nodes.end(), [](Node a, Node b)
       { return a.b > b.b; });

  vector<int> B;
  for (int i = 0; i < nodes.size(); i++)
  {
    if (i < m)
    {
      B.push_back(nodes[i].index);
    }
    else
    {
      break;
    }
  }

  return B;
}

// Choose n nodes with value a, m nodes with value b
// Return the maximum sum of all nodes
void solve(vector<Node> &nodes, int n, int m)
{
  vector<int> A = find_A(nodes, n, m);
  sort(A.begin(), A.end());

  vector<Node> rest = find_rest(nodes, A);

  vector<int> B = find_B(rest, n, m);

  long long sum = 0;
  for (int i = 0; i < A.size(); i++)
  {
    sum += nodes[A[i]].a;
  }

  for (int i = 0; i < B.size(); i++)
  {
    sum += nodes[B[i]].b;
  }

  cout << sum << endl;
  for (int i = 0; i < A.size(); i++)
  {
    cout << A[i] + 1 << " ";
  }
  cout << endl;

  for (int i = 0; i < B.size(); i++)
  {
    cout << B[i] + 1 << " ";
  }
  cout << endl;
}

int main()
{
  // nhap();
  nhap_codeforces();

  solve(nodes, n, m);
}

void nhap()
{
  cin >> k >> n >> m;

  for (int i = 1; i <= k; i++)
  {
    int a, b;
    cin >> a >> b;
    Node node = {a, b, i - 1};
    nodes.push_back(node);
  }
}

void nhap_codeforces()
{
  cin >> k >> n >> m;
  vector<int> a(k), b(k);
  for (int i = 0; i < k; i++)
    cin >> a[i];
  for (int i = 0; i < k; i++)
    cin >> b[i];

  for (int i = 0; i < k; i++)
  {
    Node node = {a[i], b[i], i};
    nodes.push_back(node);
  }
}