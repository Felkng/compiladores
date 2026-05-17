#include "ExpressaoOr.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

void ExpressaoOr::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "OR (||)" << endl;
  esquerda->debug_com_tab(tab+1);
  direita->debug_com_tab(tab+1);
}
