#pragma once

#include <memory>
#include <string>

#include "Core/Object.hpp"
#include "SyntaxKind.hpp"

namespace Minsk {

struct SyntaxToken {
  SyntaxKind kind;
  int position;
  std::string text;
  std::unique_ptr<Object> value;
};

}  // namespace Minsk
