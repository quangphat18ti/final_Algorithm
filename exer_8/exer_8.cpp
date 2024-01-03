#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int n;

vector<vector<int>> board;
vector<int> col, diag1, diag2;
vector<vector<int>> ans; // store all solutions
vector<int> check_row;
vector<int> choice_row;

void nhap()
{
  cin >> n;
}

// give one solution of N-Queen problem

void putQueenVer1(int row)
{
  if (row > n)
  {
    exit(0);
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
      putQueenVer1(row + 1);
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
  check_row.resize(n + 1, 0);
  choice_row.resize(n + 1, n);
}

void printAnswer(vector<int> &ans)
{
  for (int i = 1; i <= n; i++)
  {
    int k = ans[i];
    for (int j = 1; j <= n; j++)
    {
      if (j == k)
        cout << "X";
      else
        cout << "o";
    }
    cout << endl;
  }
}

// use Heuristic: Next Row is the row that has the least number of Queen
// use Heuristic: Put in a Column that least effect to other Queen
void putQueenVer2(int t)
{
  if (t > n)
  {
    vector<int> temp(n + 1);
    for (int i = 1; i <= n; i++)
    {
      temp[i] = check_row[i];
    }

    ans.push_back(temp);
    return;
  }

  auto find_min_row = [&]() -> int
  {
    int min_row = 1e9;
    int nrow = 0;

    for (int i = 1; i <= n; i++)
    {
      if (check_row[i])
        continue;

      choice_row[i] = 0;
      for (int j = 1; j <= n; j++)
      {
        if (col[j] || diag1[i + j] || diag2[i - j + n])
          continue;

        choice_row[i]++;
      }

      if (choice_row[i] < min_row)
      {
        min_row = choice_row[i];
        nrow = i;
      }
    }

    return nrow;
  };
  // find min_row with nrow
  int nrow = find_min_row();

  auto update_choice = []() -> int
  {
    int min_choice = 1e9;

    for (int i = 1; i <= n; i++)
    {
      if (check_row[i])
        continue;

      choice_row[i] = 0;
      for (int j = 1; j <= n; j++)
      {
        if (col[j] || diag1[i + j] || diag2[i - j + n])
          continue;

        choice_row[i]++;
      }

      min_choice = min(min_choice, choice_row[i]);
    }
    return min_choice;
  };

  vector<pair<int, int>> choice_col;
  for (int ncol = 1; ncol <= n; ncol++)
  {
    // Check if put in ncol, what is the effect to other Queen
    if (col[ncol] || diag1[nrow + ncol] || diag2[nrow - ncol + n])
      continue;

    col[ncol] = diag1[nrow + ncol] = diag2[nrow - ncol + n] = 1;
    int tam = update_choice();
    col[ncol] = diag1[nrow + ncol] = diag2[nrow - ncol + n] = 0;

    choice_col.push_back({tam, ncol});
  }

  sort(choice_col.begin(), choice_col.end());
  reverse(choice_col.begin(), choice_col.end());

  // choose the best choice
  for (pair<int, int> p : choice_col)
  {
    int ncol = p.second;

    // cout << "Time " << t << ' ' << nrow << ' ' << ncol << endl;
    col[ncol] = diag1[nrow + ncol] = diag2[nrow - ncol + n] = 1;
    check_row[nrow] = ncol;
    putQueenVer2(t + 1);

    if (!ans.empty())
      return;
    col[ncol] = diag1[nrow + ncol] = diag2[nrow - ncol + n] = 0;
    check_row[nrow] = 0;
  }
}

// Put Queen in board N * N
void solve()
{
  process_data();
  // putQueenVer1(1);

  // cout << ans.size() << endl;
  // for (int i = 0; i < ans.size(); i++)
  // {
  //   printAnswer(ans[i]);
  //   cout << endl;
  // }

  putQueenVer2(1);
  printAnswer(ans[0]);
}

int main()
{
  freopen("exer_8.inp", "r", stdin);

  nhap();
  solve();
}