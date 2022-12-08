#include <bits/stdc++.h>

using namespace std;

struct instruction {
  uint count, from, to;
};

pair<uint, string::iterator> parse_uint(string::iterator b,
                                        string::iterator e) {
  auto f = find_if(b, e, [](char c) { return '0' <= c && c <= '9'; });
  auto l = find(f, e, ' ');

  return {stoi(string(f, l)), l};
}

bool is_label(char c) { return 'A' <= c && c <= 'Z'; }

int main() {
  // READ INPUT
  string line;
  getline(cin, line);

  bool step_1 = true, step_2_skip = true;
  size_t n_stacks = (line.length() + 1) / 4;
  vector<list<char>> stacks(n_stacks);
  vector<instruction> instructions;

  do {
    if (step_1) { // first step
      auto label = find_if(line.begin(), line.end(), is_label);

      if (label == line.end()) {
        step_1 = false;
        continue;
      }

      while (label != end(line)) {
        auto stack_n = distance(line.begin(), label) / 4;
        stacks[stack_n].push_back(*label);

        label = find_if(label + 1, line.end(), is_label);
      }
    } else {
      if (step_2_skip) {
        step_2_skip = false;
        continue;
      }

      auto [count, count_end] = parse_uint(line.begin(), line.end());
      auto [from, from_end] = parse_uint(count_end, line.end());
      auto [to, _] = parse_uint(from_end, line.end());

      instructions.push_back(instruction{count, from - 1, to - 1});
    }
  } while (getline(cin, line));

  // SOLUTION
  for (auto &i : instructions) {
    auto &from = stacks[i.from], &to = stacks[i.to];
    auto move_end = next(from.begin(), i.count);

    reverse(from.begin(), move_end);

    to.splice(to.begin(), from, from.begin(), move_end);
  }

  string message = "";
  for (auto &s : stacks) {
    message += s.front();
  }

  cout << message << endl;
}
