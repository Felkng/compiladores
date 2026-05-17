#include "ExpressaoAnd.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

void ExpressaoAnd::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "AND (&&)" << endl;
  esquerda->debug_com_tab(tab+1);
  direita->debug_com_tab(tab+1);
}
