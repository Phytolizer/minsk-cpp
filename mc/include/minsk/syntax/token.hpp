#pragma once

#include <unicode/unistr.h>

#include <cstdint>
#include <string>

#include "minsk/syntax/kind.hpp"

namespace minsk::syntax {
struct Token {
  Kind::Type kind;
  std::int32_t position;
  icu::UnicodeString text;
};
}  // namespace minsk::syntax
