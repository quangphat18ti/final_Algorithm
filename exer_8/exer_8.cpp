#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int n;

vector<vector<int>> board;
vector<int> col, diag1, diag2;
vector<vector<int>> ans; // store all solutions

void nhap()
{
  cin >> n;
}

void putQueen(int row)
{
  if (row > n)
  {
    vector<int> temp(n + 1);
    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= n; j++)
      {
        if (board[i][j] == 1)
        {
          temp[i] = j;
          break;
        }
      }
    }

    ans.push_back(temp);
    return;
  }

  for (int i = 1; i <= n; i++)
  {
    if (!col[i] && !diag1[row + i] && !diag2[row - i + n])
    {
      board[row][i] = 1;
      col[i] = diag1[row + i] = diag2[row - i + n] = 1;
      putQueen(row + 1);
      board[row][i] = 0;
      col[i] = diag1[row + i] = diag2[row - i + n] = 0;
    }
  }
}

void process_data()
{
  board.resize(n + 1, vector<int>(n + 1, 0));
  col.resize(n + 1, 0);
  diag1.resize(n + n + 1, 0);
  diag2.resize(n + n + 1, 0);
}

void printAnswer(vector<int> &ans)
{
  for (int i = 1; i <= n; i++)
  {
    int k = ans[i];
    for (int j = 1; j <= n; j++)
    {
      if (j == k)
        cout << "Q";
      else
        cout << ".";
    }
    cout << endl;
  }
}

// Put Queen in board N * N
void solve()
{
  process_data();
  putQueen(1);

  cout << ans.size() << endl;
  for (int i = 0; i < ans.size(); i++)
  {
    printAnswer(ans[i]);
    cout << endl;
  }
}

int main()
{
  freopen("exer_8.inp", "r", stdin);

  nhap();
  solve();
}