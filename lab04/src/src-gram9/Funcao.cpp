#include "Funcao.hpp"
#include "../debug-util.hpp"
#include <iostream>

Funcao::Funcao() {
}

Funcao* Funcao::extrai_funcao(No_arv_parse *no) {
  if (no == NULL) return NULL;
  
  No_arv_parse* elements = no;
  if (no->simb == "Program") {
    elements = no->filhos[0];
  }
  
  No_arv_parse* element = NULL;
  while (elements != NULL && elements->regra == 1) { // Elements -> Elements Element
    element = elements->filhos[1]; // Element
    if (element->regra == 3) break; // Element -> FunctionDecl
    elements = elements->filhos[0];
  }
  
  if (element == NULL || element->regra != 3) {
    if (elements != NULL && elements->regra == 2) { // Elements -> Element
      element = elements->filhos[0];
    }
  }
  
  if (element == NULL || element->regra != 3) return NULL;
  
  No_arv_parse* func_decl = element->filhos[0]; // FunctionDecl -> KW_FN ID LPAREN Params RPAREN OptionalReturnType Block
  
  Funcao* res = new Funcao();
  res->nome_funcao = ID::extrai_ID(func_decl->filhos[1]);
  res->parametros = Variavel::extrai_lista_parametros(func_decl->filhos[3]);
  res->tipo_retorno = Tipo::extrai_Tipo(func_decl->filhos[5]);
  res->comandos = Comando::extrai_lista_comandos(func_decl->filhos[6]->filhos[1]);
  return res;
}

void debug_comandos(const vector<Comando*> &coms, int tab) {
  for (int ic = 0; ic < coms.size(); ++ic) {
    coms[ic]->debug_com_tab(tab+1);
  }  
}

void Funcao::debug() {
  if (tipo_retorno == NULL) cerr<< "TR NULL"<< endl;
  if (nome_funcao == NULL) cerr<< "NF NULL"<< endl;
  cerr << "Funcao:[retorno=" << tipo_retorno->nome() << "][nome=" << nome_funcao->nome << "]" << endl;
  cerr << "      (Param:(";
  fflush(stderr);
  for (int i_par = 0; i_par < parametros.size(); ++i_par) {
    cerr << ((parametros[i_par])->tipo == NULL ? "TIPO_INVALIDO" : (parametros[i_par])->tipo->nome()) << " " <<
      (parametros[i_par])->nome->nome << ", ";
  }
  cerr << ") { " << endl;
  debug_comandos(comandos, 1);
  cerr << "}" <<  endl;
}
