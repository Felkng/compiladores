#ifndef _STM_MOVE_HPP_
#define _STM_MOVE_HPP_
#include "Stm.hpp"
#include "Exp.hpp"

class StmMove : public Stm {
public:
  Exp* destino;
  Exp* origem;
  StmMove(Exp* dest, Exp* src);
  virtual ~StmMove();
  virtual void print() override;
};

#endif
