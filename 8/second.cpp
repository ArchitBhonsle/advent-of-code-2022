#include <bits/stdc++.h>

using namespace std;

int main() {
  // READ INPUT
  string line;
  vector<vector<uint>> forest;
  while (getline(cin, line)) {
    forest.push_back({});
    transform(line.begin(), line.end(), back_inserter(forest.back()),
              [](char c) { return c - '0'; });
  }
  for (auto &row : forest) {
    for (auto &tree : row) {
      cout << tree << ' ';
    }
    cout << endl;
  }
  cout << endl;

  // SOLUTION
  size_t nrows = forest.size(), ncols = forest.front().size();

  // :( brute force
  uint score = 0;
  for (int r = 1; r < nrows - 1; ++r) {
    for (int c = 1; c < ncols - 1; ++c) {
      uint cheight = forest[r][c];

      // look up
      uint up = 1;
      for (int i = r - 1; i - 1 >= 0 && forest[i][c] < cheight; --i)
        ++up;

      // look down
      uint down = 1;
      for (int i = r + 1; i + 1 < nrows && forest[i][c] < cheight; ++i)
        ++down;

      // look left
      uint left = 1;
      for (int i = c - 1; i - 1 >= 0 && forest[r][i] < cheight; --i)
        ++left;

      // look right
      uint right = 1;
      for (int i = c + 1; i + 1 < ncols && forest[r][i] < cheight; ++i)
        ++right;

      printf("(%d, %d): %d - %d %d %d %d = %d\n", r, c, forest[r][c], up, down,
             left, right, up * down * left * right);
      score = max(score, up * down * left * right);
    }
  }
  cout << score << endl;
}
