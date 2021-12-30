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
        kind = syntax::Kind::kIdentifierToken;
        while (true) {
          cat = static_cast<UCharCategory>(u_charType(Current()));
          if (cat == UCharCategory::U_UPPERCASE_LETTER ||
              cat == UCharCategory::U_LOWERCASE_LETTER ||
              cat == UCharCategory::U_TITLECASE_LETTER ||
              cat == UCharCategory::U_MODIFIER_LETTER ||
              cat == UCharCategory::U_LETTER_NUMBER ||
              cat == UCharCategory::U_OTHER_LETTER ||
              cat == UCharCategory::U_NON_SPACING_MARK ||
              cat == UCharCategory::U_COMBINING_SPACING_MARK ||
              cat == UCharCategory::U_DECIMAL_DIGIT_NUMBER ||
              cat == UCharCategory::U_CONNECTOR_PUNCTUATION ||
              cat == UCharCategory::U_FORMAT_CHAR ||
              (cat == UCharCategory::U_OTHER_SYMBOL &&
               (u_hasBinaryProperty(Current(), UProperty::UCHAR_EMOJI)))) {
            text.append(text_iter_.next32PostInc());
            ++position_;
          } else {
            break;
          }
        }
      } else {
        text.append(text_iter_.next32PostInc());
        ++position_;
      }
    } break;
  }

  return syntax::Token{kind, start, text};
}
