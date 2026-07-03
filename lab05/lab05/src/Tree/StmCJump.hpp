#ifndef _STM_CJUMP_HPP_
#define _STM_CJUMP_HPP_
#include "Stm.hpp"
#include "Exp.hpp"
#include <string>
using namespace std;

class StmCJump : public Stm {
public:
  Exp* expressao_booleana;
  string destino_verdade;
  string destino_falso;
  StmCJump(Exp* cond, string t, string f);
  virtual ~StmCJump();
  virtual void print() override;
};

#endif
