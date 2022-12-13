#include <bits/stdc++.h>
#include <variant>

using namespace std;

struct Noop {};
struct Addx {
  int n;
};
using Inst = variant<Noop, Addx>;

int main() {
  string line;
  vector<Inst> instructions;
  while (getline(cin, line)) {
    if (line.substr(0, 4) == "noop") {
      instructions.push_back(Noop{});
    } else if (line.substr(0, 4) == "addx") {
      Addx instruction = {stoi(line.substr(4, line.length() - 4))};
      instructions.push_back(instruction);
    } else {
    }
  }

  int cycle = 0;
  int value = 0;
  vector<int> values;
  for (auto &instruction : instructions) {
    uint next_cycle;
    int next_value = value;
    if (holds_alternative<Noop>(instruction)) {
      next_cycle = cycle + 1;
    } else if (holds_alternative<Addx>(instruction)) {
      next_cycle = cycle + 2;
      next_value = value + get<Addx>(instruction).n;
    }

    for (uint c = cycle; c < next_cycle; ++c) {
      values.push_back(value);
    }

    cycle = next_cycle;
    value = next_value;
  }
  values.push_back(value);

  for (int cycle = 0; cycle < 240; ++cycle) {
    if (cycle % 40 == 0)
      cout << endl;
    int pos = cycle % 40, val = values[cycle];

    if (pos == val || pos == val + 1 || pos == val + 2)
      cout << '#';
    else
      cout << '.';
  }
  cout << endl;
}
