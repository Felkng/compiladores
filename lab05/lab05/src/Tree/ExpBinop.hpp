#ifndef _EXP_BINOP_HPP_
#define _EXP_BINOP_HPP_
#include "Exp.hpp"
#include "Operador.hpp"
#include "../src-gram9/Expressao.hpp"

class ExpBinop : public Exp {
public:
  Operador* op;
  Exp* esq;
  Exp* dir;  
  ExpBinop(Operador* o, Exp* e, Exp* d);
  virtual ~ExpBinop();
  virtual string to_string() override;
};

#endif
