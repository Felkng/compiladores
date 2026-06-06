#ifndef _EXPRESSAOMAIORIGUAL_HPP_
#define _EXPRESSAOMAIORIGUAL_HPP_

#include "Expressao.hpp"

class ExpressaoMaiorIgual : public Expressao {
public:
  Expressao* esquerda;
  Expressao* direita;
  void debug_com_tab(int tab);
};

#endif
