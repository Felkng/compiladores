#ifndef _EXPRESSAOMENORIGUAL_HPP_
#define _EXPRESSAOMENORIGUAL_HPP_

#include "Expressao.hpp"

class ExpressaoMenorIgual : public Expressao {
public:
  Expressao* esquerda;
  Expressao* direita;
  void debug_com_tab(int tab);
};

#endif
