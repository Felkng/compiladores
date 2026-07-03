#ifndef _EXP_CONST_HPP_
#define _EXP_CONST_HPP_
#include "Exp.hpp"
#include "../src-gram9/ExpressaoValor.hpp"

class ExpConst : public Exp {
public:
  int valor;
  ExpConst(int v);
  virtual ~ExpConst();
  virtual string to_string() override;
};

#endif
