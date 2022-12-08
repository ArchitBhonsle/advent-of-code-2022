#include <bits/stdc++.h>

using namespace std;

int main() {
  // READ INPUT
  string line;
  vector<vector<int>> calories = {{}};
  while (getline(cin, line)) {
    if (line == "") {
      calories.push_back({});
    } else {
      calories.back().push_back(stoi(line));
    }
  }

  // SOLUTION
  vector<int> total_calories;
  transform(calories.begin(), calories.end(), back_inserter(total_calories),
            [](vector<int> curr) { return reduce(curr.begin(), curr.end()); });

  sort(total_calories.rbegin(), total_calories.rend());

  cout << total_calories[0] + total_calories[1] + total_calories[2] << endl;
}
