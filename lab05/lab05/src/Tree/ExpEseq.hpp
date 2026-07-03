#ifndef _EXP_ESEQ_HPP_
#define _EXP_ESEQ_HPP_
#include "Exp.hpp"
#include "Stm.hpp"
#include "../src-gram9/Expressao.hpp"

class ExpEseq : public Exp {
public:
  Stm* stm;
  Exp* exp;
  ExpEseq(Stm* s, Exp* e);
  virtual ~ExpEseq();
  virtual string to_string() override;
};

#endif
