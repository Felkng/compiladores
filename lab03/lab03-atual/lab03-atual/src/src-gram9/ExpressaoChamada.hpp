#ifndef _EXPRESSAOCHAMADA_HPP_
#define _EXPRESSAOCHAMADA_HPP_

#include "Expressao.hpp"
#include "ID.hpp"
#include <vector>

class ExpressaoChamada : public Expressao {
public:
  ID* nome;
  std::vector<Expressao*> argumentos;
  void debug_com_tab(int tab);
};

#endif
