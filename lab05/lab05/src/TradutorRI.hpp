#ifndef _TRADUTOR_RI_HPP_
#define _TRADUTOR_RI_HPP_

#include "src-gram9/Funcao.hpp"
#include "src-gram9/Comando.hpp"
#include "src-gram9/Expressao.hpp"
#include "Frame/FrameFuncao.hpp"
#include "Tree/Stm.hpp"
#include "Tree/Exp.hpp"

#include <vector>
#include <map>
#include <string>

using namespace std;

class TradutorRI {
private:
  int label_counter;
  string gera_label();

  Exp* traduz_expressao(Expressao* exp, FrameFuncao* frame, vector<map<string, Variavel*>>& scopes);
  Stm* traduz_comando(Comando* cmd, FrameFuncao* frame, vector<map<string, Variavel*>>& scopes);

public:
  TradutorRI();
  Stm* traduz_funcao(Funcao* func, FrameFuncao* frame);
};

#endif
