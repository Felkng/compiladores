#ifndef _COMANDO_LISTA_HPP_
#define _COMANDO_LISTA_HPP_
#include "Comando.hpp"
#include <vector>
using namespace std;

class ComandoLista : public Comando {
public:
  vector<Comando*> lista_comandos;
  bool is_block_scope;
  ComandoLista();
  void debug_com_tab(int tab);
};

#endif
