#ifndef _EXP_CALL_HPP_
#define _EXP_CALL_HPP_
#include "Exp.hpp"
#include "../src-gram9/Expressao.hpp"
#include<vector>
using namespace std;

class ExpCall : public Exp {
public:
  Exp* nome_funcao;
  vector<Exp*> parametros;
  ExpCall(Exp* f, vector<Exp*> p);
  virtual ~ExpCall();
  virtual string to_string() override;
};

#endif
