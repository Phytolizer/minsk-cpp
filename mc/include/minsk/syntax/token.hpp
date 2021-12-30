#pragma once

#include <cstddef>
#include <string>

#include "minsk/syntax/kind.hpp"

namespace minsk::syntax {
struct Token {
  Kind::Type kind;
  std::size_t position;
  std::string text;
};
}  // namespace minsk::syntax
