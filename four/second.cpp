#include <bits/stdc++.h>

using namespace std;

using range = pair<int, int>;

pair<int, int> parse_range(string range_string) {
  size_t del = range_string.find('-');
  string first = range_string.substr(0, del),
         second = range_string.substr(del + 1);

  return {stoi(first), stoi(second)};
}

pair<range, range> parse_pair(string pair_string) {
  size_t del = pair_string.find(',');
  string first = pair_string.substr(0, del),
         second = pair_string.substr(del + 1);

  return {parse_range(first), parse_range(second)};
}

int main() {
  // READ INPUT
  string line;
  vector<pair<range, range>> pairs;
  while (getline(cin, line)) {
    pair<range, range> p = parse_pair(line);
    pairs.push_back(p);
  }

  // SOLUTION
  int concern = ranges::count_if(pairs, [](pair<range, range> p) {
    range a = p.first, b = p.second;
    if (a > b)
      swap(a, b);

    return a.second >= b.first;
  });

  cout << concern << endl;
}
