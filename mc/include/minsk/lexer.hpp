#pragma once

#include <unicode/schriter.h>
#include <unicode/umachine.h>
#include <unicode/unistr.h>

#include <cstdint>
#include <string>

#include "minsk/syntax/token.hpp"

namespace minsk {
class Lexer {
  icu::UnicodeString text_;
  icu::StringCharacterIterator text_iter_;
  std::int32_t position_;

  UChar32 Current();

 public:
  explicit Lexer(icu::UnicodeString text);
  explicit Lexer(icu::UnicodeString&& text);

  syntax::Token Lex();
};
}  // namespace minsk
