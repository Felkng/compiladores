#ifndef _STM_LABEL_HPP_
#define _STM_LABEL_HPP_
#include "Stm.hpp"
#include<string>
using namespace std;

class StmLabel : public Stm {
public:
  string nome;
  StmLabel(string n);
  virtual ~StmLabel();
  virtual void print() override;
};

#endif
