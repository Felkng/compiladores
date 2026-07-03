#ifndef _STM_JUMP_HPP_
#define _STM_JUMP_HPP_
#include "Stm.hpp"
#include "Exp.hpp"
#include<vector>
#include<string>
using namespace std;

class StmJump : public Stm {
public:
  Exp* destino;
  vector<string> alvos;
  StmJump(Exp* dest, vector<string> targets);
  virtual ~StmJump();
  virtual void print() override;
};

#endif
