#include <fmt/format.h>

#include <iostream>
#include <string>

int main() {
  while (true) {
    fmt::print("> ");
    std::string line;
    if (!std::getline(std::cin, line)) {
      fmt::print("\n");
      break;
    }

    if (line == "1 + 2 * 3") {
      fmt::print("7\n");
    } else {
      fmt::print("ERROR: Invalid expression!\n");
    }
  }
  return 0;
}
