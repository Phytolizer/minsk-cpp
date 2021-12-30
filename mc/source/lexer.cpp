#include "minsk/lexer.hpp"

#include <unicode/uchar.h>
#include <unicode/unistr.h>
#include <unicode/urename.h>
#include <unicode/ustdio.h>

#include "minsk/syntax/kind.hpp"

UChar32 minsk::Lexer::Current() {
  if (!text_iter_.hasNext()) {
    return '\0';
  }
  return text_iter_.current32();
}

minsk::Lexer::Lexer(icu::UnicodeString text)
    : text_(std::move(text)), text_iter_(text), position_(0) {}
minsk::Lexer::Lexer(icu::UnicodeString&& text)
    : text_(std::move(text)), text_iter_(text), position_(0) {}

minsk::syntax::Token minsk::Lexer::Lex() {
  auto kind = syntax::Kind::kBadToken;
  icu::UnicodeString text;
  std::int32_t start = position_;

  switch (Current()) {
    case '\0':
      kind = syntax::Kind::kEndOfFileToken;
      break;
    case '0' ... '9':
      kind = syntax::Kind::kNumberToken;
      while (Current() >= '0' && Current() <= '9') {
        text.append(text_iter_.next32PostInc());
      }
      break;
    case '_':
    default: {
      UCharCategory cat = static_cast<UCharCategory>(u_charType(Current()));
      if (cat == UCharCategory::U_UPPERCASE_LETTER ||
          cat == UCharCategory::U_LOWERCASE_LETTER ||
          cat == UCharCategory::U_TITLECASE_LETTER ||
          cat == UCharCategory::U_MODIFIER_LETTER ||
          cat == UCharCategory::U_LETTER_NUMBER ||
          cat == UCharCategory::U_OTHER_LETTER || Current() == '_') {
        bool ident = true;
        while (ident) {
          switch (u_charType(Current())) {
            case UCharCategory::U_UPPERCASE_LETTER:
            case UCharCategory::U_LOWERCASE_LETTER:
            case UCharCategory::U_TITLECASE_LETTER:
            case UCharCategory::U_MODIFIER_LETTER:
            case UCharCategory::U_LETTER_NUMBER:
            case UCharCategory::U_OTHER_LETTER:
            case UCharCategory::U_NON_SPACING_MARK:
            case UCharCategory::U_COMBINING_SPACING_MARK:
            case UCharCategory::U_DECIMAL_DIGIT_NUMBER:
            case UCharCategory::U_CONNECTOR_PUNCTUATION:
            case UCharCategory::U_FORMAT_CHAR:
              text.append(text_iter_.next32PostInc());
              ++position_;
              break;
            default:
              ident = false;
          }
        }
      } else {
        text.append(text_iter_.next32PostInc());
      }
    } break;
  }

  return syntax::Token{kind, start, text};
}
