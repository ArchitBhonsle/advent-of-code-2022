#include <bits/stdc++.h>

using namespace std;

int main() {
  // READING INPUT
  string line;
  getline(cin, line);

  // SOLTUION
  unordered_set<char> used;
  auto i = line.begin(), j = i;
  uint stage = 0; // 0 is expansion, 1 is contraction

  while (i <= line.end() && j <= line.end()) {
    if (!stage) {               // expansion
      if (!used.contains(*j)) { // can expand
        used.insert(*j);
        ++j;

        if (distance(i, j) == 14) { // sequence found
          cout << distance(line.begin(), j) << endl;
          return 0;
        }
      } else { // can not expand
        stage = 1;
      }
    } else { // contraction
      for (auto k = i; i < j; ++k) {
        if (*k != *j) {
          used.erase(*k);
        } else {
          i = k + 1;
          ++j;
          break;
        }
      }
      stage = 0;
    }
  }
}
