#include "ComandoWhile.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

void ComandoWhile::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "WHILE (" << endl;
  condicao->debug_com_tab(tab+1);
  tab3(tab);
  cerr << ") {" << endl;
  bloco->debug_com_tab(tab+1);
  tab3(tab);
  cerr << "}" << endl;
}
