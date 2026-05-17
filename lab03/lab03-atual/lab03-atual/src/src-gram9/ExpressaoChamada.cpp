#include "ExpressaoChamada.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

void ExpressaoChamada::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "CALL " << nome->nome << "()" << endl;
  for (int i=0; i<argumentos.size(); ++i) {
    argumentos[i]->debug_com_tab(tab+1);
  }
}
