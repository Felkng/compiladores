#include "ExpressaoMenosUnario.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

void ExpressaoMenosUnario::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "UNARY MINUS (-)" << endl;
  expressao->debug_com_tab(tab+1);
}
