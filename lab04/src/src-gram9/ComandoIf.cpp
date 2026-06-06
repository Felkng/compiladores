#include "ComandoIf.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

void ComandoIf::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "IF (" << endl;
  condicao->debug_com_tab(tab+1);
  tab3(tab);
  cerr << ") {" << endl;
  bloco_if->debug_com_tab(tab+1);
  if (bloco_else != NULL) {
    tab3(tab);
    cerr << "} ELSE {" << endl;
    bloco_else->debug_com_tab(tab+1);
  }
  tab3(tab);
  cerr << "}" << endl;
}
