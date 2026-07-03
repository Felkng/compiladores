#ifndef _EXPRESSAOMENOSUNARIO_HPP_
#define _EXPRESSAOMENOSUNARIO_HPP_

#include "Expressao.hpp"

class ExpressaoMenosUnario : public Expressao {
public:
  Expressao* expressao;
  void debug_com_tab(int tab);
};

#endif
