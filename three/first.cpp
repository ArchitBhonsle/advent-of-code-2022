#include <bits/stdc++.h>
#include <iterator>

using namespace std;

int get_priority(char c) { return c < 'a' ? c - 'A' + 27 : c - 'a' + 1; }

string::iterator dedup(string::iterator b, string::iterator e) {
  sort(b, e);
  return unique(b, e);
}

int main() {
  // READ INPUT
  string line;
  vector<string> sacks;
  while (getline(cin, line)) {
    sacks.push_back(line);
  }

  // SOLUTON
  vector<int> items;
  transform(sacks.begin(), sacks.end(), back_inserter(items), [](string sack) {
    size_t len = sack.length();
    auto fbegin = sack.begin(), fterm = sack.begin() + len / 2;
    auto sbegin = sack.begin() + len / 2, sterm = sack.end();

    auto fend = dedup(fbegin, fterm), send = dedup(sbegin, sterm);

    auto item = find_if(fbegin, fend, [&](const char i) {
      auto it = lower_bound(sbegin, send, i);
      return it != send && *it == i;
    });

    return *item;
  });

  vector<int> priorities;
  transform(items.begin(), items.end(), back_inserter(priorities),
            [](const char c) { return get_priority(c); });

  cout << reduce(priorities.begin(), priorities.end()) << endl;
}
