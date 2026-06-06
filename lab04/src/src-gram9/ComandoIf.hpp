#ifndef _COMANDOIF_HPP_
#define _COMANDOIF_HPP_

#include "Comando.hpp"
#include "Expressao.hpp"
#include "ComandoLista.hpp"

class ComandoIf : public Comando {
public:
  Expressao* condicao;
  ComandoLista* bloco_if;
  ComandoLista* bloco_else;

  void debug_com_tab(int tab);
};

#endif
