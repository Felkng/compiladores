#include "Variavel.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

vector<Variavel*> Variavel::extrai_lista_nao_vazia_parametros(No_arv_parse* no) {
  // ParamList
  vector<Variavel*> res;
  if (no->regra == 20) { // ParamList -> Param
    res.push_back(extrai_variavel_P(no->filhos[0]));
    return res;
  }
  // Tem que ser regra 19. ParamList -> ParamList COMMA Param
  res = extrai_lista_nao_vazia_parametros(no->filhos[0]);
  res.push_back(extrai_variavel_P(no->filhos[2]));
  return res;
}

vector<Variavel *> Variavel::extrai_lista_parametros(No_arv_parse* no) {
  // Params
  if (no->regra == 18) return vector<Variavel*>(); // Params ->
  // Tem que ser regra 17, Params -> ParamList
  return extrai_lista_nao_vazia_parametros(no->filhos[0]);
}

Variavel* Variavel::extrai_variavel_P(No_arv_parse* no) {
  Variavel* res = new Variavel();
  // 21) Param -> ID COLON Type
  res->nome = ID::extrai_ID(no->filhos[0]);
  res->tipo = Tipo::extrai_Tipo(no->filhos[2]);
  return res;
}

void Variavel::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "[" << nome->nome << ":" <<  (tipo == NULL ? "TIPO_INVALIDO" : tipo->nome()) << "] Variavel Declarada" << endl;
}
