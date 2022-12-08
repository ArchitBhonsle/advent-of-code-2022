#include <bits/stdc++.h>

using namespace std;

int get_priority(char c) { return c < 'a' ? c - 'A' + 27 : c - 'a' + 1; }

string deduped(string s) {
  sort(s.begin(), s.end());
  auto dedup_end = unique(s.begin(), s.end());

  return s.substr(0, distance(s.begin(), dedup_end));
}

int main() {
  // READ INPUT
  string line;
  vector<array<string, 3>> groups = {};
  int index = 0;
  while (getline(cin, line)) {
    if (index == 0)
      groups.push_back({});

    groups.back()[index] = deduped(line);

    index = (index + 1) % 3;
  }
  // each of the sacks are sorted and deduped

  // SOLUTION
  vector<char> badges;
  transform(groups.begin(), groups.end(), back_inserter(badges),
            [](array<string, 3> g) {
              string f = g[0], s = g[1], t = g[2];

              auto f_end = remove_if(f.begin(), f.end(), [&](const char i) {
                auto it = lower_bound(s.begin(), s.end(), i);
                return it != s.end() && *it != i;
              });

              auto item = find_if(f.begin(), f_end, [&](const char i) {
                auto it = lower_bound(t.begin(), t.end(), i);
                return it != t.end() && *it == i;
              });

              return *item;
            });

  vector<int> priorities;
  transform(badges.begin(), badges.end(), back_inserter(priorities),
            [](const char c) { return get_priority(c); });

  cout << reduce(priorities.begin(), priorities.end()) << endl;
}
