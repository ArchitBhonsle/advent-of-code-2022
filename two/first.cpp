#include <algorithm>
#include <bits/stdc++.h>
#include <numeric>

using namespace std;

int shape_score(char me) { return me - 'A' + 1; }

int outcome_score(char op, char me) {
  if (op == me) // tie
    return 3;
  else if ((op == 'A' && me == 'B') || (op == 'B' && me == 'C') ||
           (op == 'C' && me == 'A')) // win
    return 6;
  else // lose
    return 0;
}

int main() {
  // READ INPUT
  string line;
  vector<pair<char, char>> guide;
  while (getline(cin, line)) {
    cout << line[0] << " " << line[2] << endl;
    guide.push_back({line[0], line[2] - 'X' + 'A'});
  }

  // SOLUTION
  cout << transform_reduce(guide.begin(), guide.end(), 0, plus<>(),
                           [](pair<char, char> g) {
                             return shape_score(g.second) +
                                    outcome_score(g.first, g.second);
                           })
       << endl;
}
