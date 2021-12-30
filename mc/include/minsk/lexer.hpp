#pragma once

#include <cstddef>
#include <string>

#include "minsk/syntax/token.hpp"

namespace minsk {
class Lexer {
  std::string text_;
  std::size_t position_;

 public:
  explicit Lexer(std::string text);
  explicit Lexer(std::string&& text);

  syntax::Token Lex();
};
}  // namespace minsk
