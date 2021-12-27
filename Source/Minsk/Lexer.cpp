#include "Lexer.hpp"
#include "Source/Minsk/Core/Integer.hpp"
#include "Source/Minsk/Core/Object.hpp"
#include "Source/Minsk/SyntaxKind.hpp"
#include <cctype>
#include <sstream>

char Minsk::Lexer::Current() const
{
    if (m_position >= m_text.size())
    {
        return '\0';
    }
    return m_text[m_position];
}

Minsk::Lexer::Lexer(const std::string& text) : m_text{text}, m_position{0}
{
}

Minsk::SyntaxToken Minsk::Lexer::Lex()
{
    int start = m_position;
    auto kind = SyntaxKind::BAD_TOKEN;
    std::unique_ptr<Object> value = nullptr;

    if (std::isdigit(Current()))
    {
        while (std::isdigit(Current()))
        {
            ++m_position;
        }
        std::istringstream stream{m_text.substr(start, m_position - start)};
        int ival;
        if (!(stream >> ival))
        {
            // TODO: error handling
        }
        value = std::make_unique<Integer>(ival);
        kind = SyntaxKind::NUMBER_TOKEN;
    }
    else if (std::isspace(Current()))
    {
        while (std::isspace(Current()))
        {
            ++m_position;
        }
        kind = SyntaxKind::WHITESPACE_TOKEN;
    }
    else
    {
        switch (Current())
        {
        case '+':
            kind = SyntaxKind::PLUS_TOKEN;
            ++m_position;
            break;
        case '-':
            kind = SyntaxKind::MINUS_TOKEN;
            ++m_position;
            break;
        case '*':
            kind = SyntaxKind::STAR_TOKEN;
            ++m_position;
            break;
        case '/':
            kind = SyntaxKind::SLASH_TOKEN;
            ++m_position;
            break;
        case '(':
            kind = SyntaxKind::OPEN_PARENTHESIS_TOKEN;
            ++m_position;
            break;
        case ')':
            kind = SyntaxKind::CLOSE_PARENTHESIS_TOKEN;
            ++m_position;
            break;
        default:
            ++m_position;
            break;
        }
    }

    return SyntaxToken{
        .kind = kind,
        .position = start,
        .text = m_text.substr(start, m_position - start),
        .value = std::move(value),
    };
}
