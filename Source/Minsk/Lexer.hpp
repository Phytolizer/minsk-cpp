#pragma once

#include <string>

#include "SyntaxToken.hpp"

namespace Minsk {

class Lexer {
  std::string m_text;
  int m_position;

  char Current() const;

 public:
  explicit Lexer(const std::string& text);

  SyntaxToken Lex();
};

}  // namespace Minsk
