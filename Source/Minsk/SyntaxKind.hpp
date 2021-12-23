#pragma once

namespace Minsk
{

#define MINSK_SYNTAX_KIND_VARIANTS_                                                                                    \
    X(PLUS_TOKEN)                                                                                                      \
    X(MINUS_TOKEN)                                                                                                     \
    X(STAR_TOKEN)                                                                                                      \
    X(SLASH_TOKEN)                                                                                                     \
    X(NUMBER_TOKEN)                                                                                                    \
    X(WHITESPACE_TOKEN)                                                                                                \
    X(BAD_TOKEN)                                                                                                       \
    X(END_OF_FILE_TOKEN)

enum class SyntaxKind
{
#define X(x) x,
    MINSK_SYNTAX_KIND_VARIANTS_
#undef X
};

} // namespace Minsk
