#include <bits/stdc++.h>
#include <variant>

using namespace std;

struct Noop {};
struct Addx {
  int n;
};
using Inst = variant<Noop, Addx>;

bool is_important(uint cycle) {
  return (cycle >= 20 && ((cycle - 20) % 40) == 0);
}

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

  uint cycle = 1;
  int value = 1, result = 0;
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
      if (!is_important(c))
        continue;

      result += (value * c);
    }

    cycle = next_cycle;
    value = next_value;
  }

  if (is_important(cycle)) {
    result += (value * cycle);
  }

  cout << result << endl;
}
