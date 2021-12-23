#pragma once

#include "Core/Object.hpp"
#include "SyntaxKind.hpp"
#include <memory>
#include <string>

namespace Minsk
{

struct SyntaxToken
{
    SyntaxKind kind;
    int position;
    std::string text;
    std::unique_ptr<Object> value;
};

} // namespace Minsk
