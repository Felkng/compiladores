#ifndef _EXPRESSAODIFERENTE_HPP_
#define _EXPRESSAODIFERENTE_HPP_

#include "Expressao.hpp"

class ExpressaoDiferente : public Expressao {
public:
  Expressao* esquerda;
  Expressao* direita;
  void debug_com_tab(int tab);
};

#endif
