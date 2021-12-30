#include <unicode/unistr.h>
#include <unicode/ustream.h>

#include <iostream>
#include <minsk/lexer.hpp>

#include "minsk/syntax/kind.hpp"

int main() {
  icu::UnicodeString text = "abc🙃";
  minsk::Lexer lexer(text);

  for (auto tok = lexer.Lex(); tok.kind != minsk::syntax::Kind::kEndOfFileToken;
       tok = lexer.Lex()) {
    std::cout << tok.kind.Value() << ": " << tok.text << std::endl;
  }
  return 0;
}
