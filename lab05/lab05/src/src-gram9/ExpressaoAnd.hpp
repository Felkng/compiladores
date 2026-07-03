#ifndef _EXPRESSAOAND_HPP_
#define _EXPRESSAOAND_HPP_

#include "Expressao.hpp"

class ExpressaoAnd : public Expressao {
public:
  Expressao* esquerda;
  Expressao* direita;
  void debug_com_tab(int tab);
};

#endif
