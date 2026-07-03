#ifndef _EXP_MEM_HPP_
#define _EXP_MEM_HPP_
#include "Exp.hpp"
#include "../src-gram9/Expressao.hpp"

class ExpMem : public Exp {
public:
  Exp* endereco;
  ExpMem(Exp* e);
  virtual ~ExpMem();
  virtual string to_string() override;
};

#endif
