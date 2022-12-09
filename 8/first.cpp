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

  // SOLUTION
  size_t nrows = forest.size(), ncols = forest.front().size();

  // creating the grid
  vector<vector<bool>> visible(
      nrows, vector<bool>(ncols, false)); // if a particular tree is visible
  for (size_t r = 0; r < nrows; ++r)
    for (size_t c = 0; c < ncols; ++c)
      if (r == 0 || r == nrows - 1 || c == 0 || c == ncols - 1)
        visible[r][c] = true;

  // look from the left
  for (size_t r = 1; r < nrows - 1; ++r) {
    uint largest = forest[r][0];
    for (size_t c = 1; c < ncols - 1; ++c) {
      if (forest[r][c] > largest) {
        visible[r][c] = true;
        largest = forest[r][c];
      }
    }
  }

  // look from the top
  for (size_t c = 1; c < ncols - 1; ++c) {
    uint largest = forest[0][c];
    for (size_t r = 1; r < nrows - 1; ++r) {
      if (forest[r][c] > largest) {
        visible[r][c] = true;
        largest = forest[r][c];
      }
    }
  }

  // look from the right
  for (size_t r = 1; r < nrows - 1; ++r) {
    uint largest = forest[r][ncols - 1];
    for (size_t c = ncols - 2; c > 0; --c) {
      if (forest[r][c] > largest) {
        visible[r][c] = true;
        largest = forest[r][c];
      }
    }
  }

  // look from the bottom
  for (size_t c = 1; c < ncols; ++c) {
    uint largest = forest[nrows - 1][c];
    for (size_t r = nrows - 2; r > 0; --r) {
      if (forest[r][c] > largest) {
        visible[r][c] = true;
        largest = forest[r][c];
      }
    }
  }

  // calculating solution
  uint nvisible = 0;
  for (size_t r = 0; r < nrows; ++r)
    for (size_t c = 0; c < ncols; ++c)
      nvisible += visible[r][c];

  cout << nvisible << endl;
}
