#ifndef _EXPRESSAOOR_HPP_
#define _EXPRESSAOOR_HPP_

#include "Expressao.hpp"

class ExpressaoOr : public Expressao {
public:
  Expressao* esquerda;
  Expressao* direita;
  void debug_com_tab(int tab);
};

#endif
