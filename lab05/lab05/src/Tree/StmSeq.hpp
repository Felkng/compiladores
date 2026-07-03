#ifndef _STM_SEQ_HPP_
#define _STM_SEQ_HPP_
#include "Stm.hpp"

class StmSeq : public Stm {
public:
  Stm* esq;
  Stm* dir;
  StmSeq(Stm* l, Stm* r);
  virtual ~StmSeq();
  virtual void print() override;
};

#endif
