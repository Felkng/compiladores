#include "Tipo.hpp"
#include <algorithm>

Tipo::Tipo(Valor valor) {
  this->valor = valor;
}

string Tipo::nome() const {
  switch(valor) {
  case INT:
    return "INT";
  case FLOAT:
    return "FLOAT";
  case BOOL:
    return "BOOL";
  }
  return "";
}

string normaliza_nome_tipo(string nome) {
  transform(nome.begin(), nome.end(), nome.begin(), ::toupper);
  return nome;
}

Tipo* tipo_por_nome(string nome) {
  nome = normaliza_nome_tipo(nome);
  if (nome == "I32" || nome == "I64" || nome == "INT") return new Tipo(Tipo::INT);
  if (nome == "F32" || nome == "F64" || nome == "FLOAT") return new Tipo(Tipo::FLOAT);
  if (nome == "BOOL" || nome == "BOOLEAN") return new Tipo(Tipo::BOOL);
  return NULL;
}

Tipo* Tipo::extrai_Tipo(No_arv_parse* no) {
  if (no == NULL) return NULL;
  
  if (no->simb == "OptionalReturnType") {
    if (no->regra == 16) return NULL; // sem retorno
    // regra 15: ARROW Type
    return extrai_Tipo(no->filhos[1]);
  }
  
  if (no->simb == "Type") {
    if (no->regra == 22) { // Type -> ID
      return tipo_por_nome(no->filhos[0]->dado_extra);
    }
    // we don't care about references or arrays for now
    return NULL;
  }
  
  return NULL;
}

Tipo* Tipo::extrai_tipo_literal(No_arv_parse* no) {
  if (no == NULL) return NULL;
  if (no->simb == "DEC_VAL" || no->simb == "LIT_INT_DEC") return new Tipo(INT);
  if (no->simb == "FLOAT_VAL" || no->simb == "LIT_FLOAT") return new Tipo(FLOAT);
  if (no->simb == "BOOL_VAL" || no->simb == "LIT_BOOL") return new Tipo(BOOL);
  return NULL;
}
