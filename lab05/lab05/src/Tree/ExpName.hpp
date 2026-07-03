#ifndef _EXP_NAME_HPP_
#define _EXP_NAME_HPP_
#include <string>
#include "Exp.hpp"
#include "../src-gram9/Expressao.hpp"
using namespace std;

class ExpName : public Exp {
public:
  string nome;
  ExpName(string n);
  virtual ~ExpName();
  virtual string to_string() override;
};

#endif
