#ifndef _EXPRESSAOCAST_HPP_
#define _EXPRESSAOCAST_HPP_

#include "Expressao.hpp"
#include "Tipo.hpp"

class ExpressaoCast : public Expressao {
public:
  Expressao* expressao;
  Tipo* tipo;
  void debug_com_tab(int tab);
};

#endif
