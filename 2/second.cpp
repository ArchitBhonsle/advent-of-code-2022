#include <algorithm>
#include <bits/stdc++.h>
#include <numeric>

using namespace std;

int outcome_score(char out) { return (out - 'X') * 3; }

char my_shape(char opp, char out) {
  char me = ((opp - 'A') + (out - 'Y')) % 3;
  if (me < 0)
    me += 3;
  return me + 'A';
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
