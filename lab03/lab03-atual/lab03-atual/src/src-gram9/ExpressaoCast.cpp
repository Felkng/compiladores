#include "ExpressaoCast.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

void ExpressaoCast::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "CAST (" << tipo->nome() << ")" << endl;
  expressao->debug_com_tab(tab+1);
}
