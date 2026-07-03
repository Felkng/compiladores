#ifndef _EXPRESSAOMAIOR_HPP_
#define _EXPRESSAOMAIOR_HPP_

#include "Expressao.hpp"

class ExpressaoMaior : public Expressao {
public:
  Expressao* esquerda;
  Expressao* direita;
  void debug_com_tab(int tab);
};

#endif
