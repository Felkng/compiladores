#ifndef _STM_EXP_HPP_
#define _STM_EXP_HPP_
#include "Stm.hpp"
#include "Exp.hpp"

class StmExp : public Stm {
public:
  Exp* exp;
  StmExp(Exp* e);
  virtual ~StmExp();
  virtual void print() override;
};

#endif
