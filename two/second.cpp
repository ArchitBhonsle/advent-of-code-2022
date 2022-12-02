#include <algorithm>
#include <bits/stdc++.h>
#include <numeric>

using namespace std;

int outcome_score(char out) {
  switch (out) {
  case 'X':
    return 0;
  case 'Y':
    return 3;
  case 'Z':
    return 6;
  default:
    return -1;
  }
}

char my_shape(char opp, char out) {
  switch (out) {
  case 'X':
    return (opp - 'A' + 2) % 3 + 'A';
  case 'Y':
    return opp;
  case 'Z':
    return (opp - 'A' + 1) % 3 + 'A';
  default:
    return -1;
  }
}

int shape_score(char me) { return me - 'A' + 1; }

int main() {
  // READ INPUT
  string line;
  vector<pair<char, char>> guide;
  while (getline(cin, line)) {
    guide.push_back({line[0], line[2]});
  }

  // SOLUTION
  cout << transform_reduce(guide.begin(), guide.end(), 0, plus<>(),
                           [](pair<char, char> g) {
                             return outcome_score(g.second) +
                                    shape_score(my_shape(g.first, g.second));
                           })
       << endl;
}
