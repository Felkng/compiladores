#ifndef _COMANDOWHILE_HPP_
#define _COMANDOWHILE_HPP_

#include "Comando.hpp"
#include "Expressao.hpp"
#include "ComandoLista.hpp"

class ComandoWhile : public Comando {
public:
  Expressao* condicao;
  ComandoLista* bloco;

  void debug_com_tab(int tab);
};

#endif
