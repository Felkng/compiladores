#ifndef _EXP_HPP_
#define _EXP_HPP_
#include <string>
#include "../src-gram9/Expressao.hpp"
using namespace std;

class Exp {
public:
  virtual ~Exp() {}
  virtual string to_string() = 0;
};

#endif
