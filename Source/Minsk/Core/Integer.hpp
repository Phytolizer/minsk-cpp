#pragma once

#include "Object.hpp"

namespace Minsk {

class Integer : public Object {
 public:
  int value;

  explicit Integer(int value);
};

}  // namespace Minsk
