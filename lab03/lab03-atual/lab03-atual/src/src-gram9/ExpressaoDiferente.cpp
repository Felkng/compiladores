#include "ExpressaoDiferente.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

void ExpressaoDiferente::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "DIFERENTE (!=)" << endl;
  esquerda->debug_com_tab(tab+1);
  direita->debug_com_tab(tab+1);
}
