#include "Analisador.hpp"
#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

Analisador::Analisador() {
  is_returning = false;
}

void Analisador::entra_escopo() {
  escopos.push_back(map<string, ValorLiteral>());
}

void Analisador::sai_escopo() {
  if (!escopos.empty()) {
    escopos.pop_back();
  }
}

void Analisador::declara_var(string nome, Tipo* tipo) {
  if (escopos.empty()) return;
  ValorLiteral v;
  v.tipo = tipo;
  if (tipo->valor == Tipo::INT) v.valor_int = 0;
  else if (tipo->valor == Tipo::FLOAT) v.valor_float = 0.0;
  else if (tipo->valor == Tipo::BOOL) v.valor_bool = false;
  escopos.back()[nome] = v;
}

void Analisador::atribui_var(string nome, ValorLiteral val) {
  for (int i = escopos.size() - 1; i >= 0; --i) {
    if (escopos[i].find(nome) != escopos[i].end()) {
      Tipo* t_var = escopos[i][nome].tipo;
      if (t_var->valor != val.tipo->valor) {
        cerr << "ERRO SEMANTICO: Tipos incompativeis na atribuicao de " << nome << endl;
        exit(1);
      }
      escopos[i][nome] = val;
      ultimo_atribuido = val;
      return;
    }
  }
  cerr << "ERRO SEMANTICO: Variavel nao declarada " << nome << endl;
  exit(1);
}

ValorLiteral Analisador::le_var(string nome) {
  for (int i = escopos.size() - 1; i >= 0; --i) {
    if (escopos[i].find(nome) != escopos[i].end()) {
      return escopos[i][nome];
    }
  }
  cerr << "ERRO SEMANTICO: Variavel nao declarada " << nome << endl;
  exit(1);
}

ValorLiteral Analisador::avalia_expressao(Expressao* exp) {
  ValorLiteral nulo;
  nulo.tipo = NULL;
  if (exp == NULL) return nulo;

  if (ExpressaoValor* ev = dynamic_cast<ExpressaoValor*>(exp)) {
    return *(ev->valor);
  }
  if (ExpressaoVariavel* evar = dynamic_cast<ExpressaoVariavel*>(exp)) {
    if (evar->nome->nome == "true") {
      ValorLiteral vl;
      vl.tipo = new Tipo(Tipo::BOOL);
      vl.valor_bool = true;
      return vl;
    }
    if (evar->nome->nome == "false") {
      ValorLiteral vl;
      vl.tipo = new Tipo(Tipo::BOOL);
      vl.valor_bool = false;
      return vl;
    }
    return le_var(evar->nome->nome);
  }
  if (ExpressaoSoma* op = dynamic_cast<ExpressaoSoma*>(exp)) {
    ValorLiteral esq = avalia_expressao(op->esquerda);
    ValorLiteral dir = avalia_expressao(op->direita);
    if (esq.tipo->valor != dir.tipo->valor || esq.tipo->valor == Tipo::BOOL) {
      cerr << "ERRO SEMANTICO: Tipos incompativeis para soma" << endl; exit(1);
    }
    ValorLiteral res; res.tipo = esq.tipo;
    if (res.tipo->valor == Tipo::INT) res.valor_int = esq.valor_int + dir.valor_int;
    else res.valor_float = esq.valor_float + dir.valor_float;
    return res;
  }
  if (ExpressaoSubtracao* op = dynamic_cast<ExpressaoSubtracao*>(exp)) {
    ValorLiteral esq = avalia_expressao(op->esquerda);
    ValorLiteral dir = avalia_expressao(op->direita);
    if (esq.tipo->valor != dir.tipo->valor || esq.tipo->valor == Tipo::BOOL) {
      cerr << "ERRO SEMANTICO: Tipos incompativeis para subtracao" << endl; exit(1);
    }
    ValorLiteral res; res.tipo = esq.tipo;
    if (res.tipo->valor == Tipo::INT) res.valor_int = esq.valor_int - dir.valor_int;
    else res.valor_float = esq.valor_float - dir.valor_float;
    return res;
  }
  if (ExpressaoMultiplicacao* op = dynamic_cast<ExpressaoMultiplicacao*>(exp)) {
    ValorLiteral esq = avalia_expressao(op->esquerda);
    ValorLiteral dir = avalia_expressao(op->direita);
    if (esq.tipo->valor != dir.tipo->valor || esq.tipo->valor == Tipo::BOOL) {
      cerr << "ERRO SEMANTICO: Tipos incompativeis para multiplicacao" << endl; exit(1);
    }
    ValorLiteral res; res.tipo = esq.tipo;
    if (res.tipo->valor == Tipo::INT) res.valor_int = esq.valor_int * dir.valor_int;
    else res.valor_float = esq.valor_float * dir.valor_float;
    return res;
  }
  if (ExpressaoDivisao* op = dynamic_cast<ExpressaoDivisao*>(exp)) {
    ValorLiteral esq = avalia_expressao(op->esquerda);
    ValorLiteral dir = avalia_expressao(op->direita);
    if (esq.tipo->valor != dir.tipo->valor || esq.tipo->valor == Tipo::BOOL) {
      cerr << "ERRO SEMANTICO: Tipos incompativeis para divisao" << endl; exit(1);
    }
    ValorLiteral res; res.tipo = esq.tipo;
    if (res.tipo->valor == Tipo::INT) res.valor_int = esq.valor_int / dir.valor_int;
    else res.valor_float = esq.valor_float / dir.valor_float;
    return res;
  }
  if (ExpressaoMod* op = dynamic_cast<ExpressaoMod*>(exp)) {
    ValorLiteral esq = avalia_expressao(op->esquerda);
    ValorLiteral dir = avalia_expressao(op->direita);
    if (esq.tipo->valor != dir.tipo->valor || esq.tipo->valor != Tipo::INT) {
      cerr << "ERRO SEMANTICO: Tipos incompativeis para mod" << endl; exit(1);
    }
    ValorLiteral res; res.tipo = esq.tipo;
    res.valor_int = esq.valor_int % dir.valor_int;
    return res;
  }
  if (ExpressaoMenor* op = dynamic_cast<ExpressaoMenor*>(exp)) {
    ValorLiteral esq = avalia_expressao(op->esquerda);
    ValorLiteral dir = avalia_expressao(op->direita);
    if (esq.tipo->valor != dir.tipo->valor) {
      cerr << "ERRO SEMANTICO: Tipos incompativeis para <" << endl; exit(1);
    }
    ValorLiteral res; res.tipo = new Tipo(Tipo::BOOL);
    if (esq.tipo->valor == Tipo::INT) res.valor_bool = esq.valor_int < dir.valor_int;
    else if (esq.tipo->valor == Tipo::FLOAT) res.valor_bool = esq.valor_float < dir.valor_float;
    else res.valor_bool = esq.valor_bool < dir.valor_bool;
    return res;
  }
  if (ExpressaoMaior* op = dynamic_cast<ExpressaoMaior*>(exp)) {
    ValorLiteral esq = avalia_expressao(op->esquerda);
    ValorLiteral dir = avalia_expressao(op->direita);
    if (esq.tipo->valor != dir.tipo->valor) {
      cerr << "ERRO SEMANTICO: Tipos incompativeis para >" << endl; exit(1);
    }
    ValorLiteral res; res.tipo = new Tipo(Tipo::BOOL);
    if (esq.tipo->valor == Tipo::INT) res.valor_bool = esq.valor_int > dir.valor_int;
    else if (esq.tipo->valor == Tipo::FLOAT) res.valor_bool = esq.valor_float > dir.valor_float;
    else res.valor_bool = esq.valor_bool > dir.valor_bool;
    return res;
  }
  if (ExpressaoMenorIgual* op = dynamic_cast<ExpressaoMenorIgual*>(exp)) {
    ValorLiteral esq = avalia_expressao(op->esquerda);
    ValorLiteral dir = avalia_expressao(op->direita);
    if (esq.tipo->valor != dir.tipo->valor) {
      cerr << "ERRO SEMANTICO: Tipos incompativeis para <=" << endl; exit(1);
    }
    ValorLiteral res; res.tipo = new Tipo(Tipo::BOOL);
    if (esq.tipo->valor == Tipo::INT) res.valor_bool = esq.valor_int <= dir.valor_int;
    else if (esq.tipo->valor == Tipo::FLOAT) res.valor_bool = esq.valor_float <= dir.valor_float;
    else res.valor_bool = esq.valor_bool <= dir.valor_bool;
    return res;
  }
  if (ExpressaoMaiorIgual* op = dynamic_cast<ExpressaoMaiorIgual*>(exp)) {
    ValorLiteral esq = avalia_expressao(op->esquerda);
    ValorLiteral dir = avalia_expressao(op->direita);
    if (esq.tipo->valor != dir.tipo->valor) {
      cerr << "ERRO SEMANTICO: Tipos incompativeis para >=" << endl; exit(1);
    }
    ValorLiteral res; res.tipo = new Tipo(Tipo::BOOL);
    if (esq.tipo->valor == Tipo::INT) res.valor_bool = esq.valor_int >= dir.valor_int;
    else if (esq.tipo->valor == Tipo::FLOAT) res.valor_bool = esq.valor_float >= dir.valor_float;
    else res.valor_bool = esq.valor_bool >= dir.valor_bool;
    return res;
  }
  if (ExpressaoIgualdade* op = dynamic_cast<ExpressaoIgualdade*>(exp)) {
    ValorLiteral esq = avalia_expressao(op->esquerda);
    ValorLiteral dir = avalia_expressao(op->direita);
    if (esq.tipo->valor != dir.tipo->valor) {
      cerr << "ERRO SEMANTICO: Tipos incompativeis para ==" << endl; exit(1);
    }
    ValorLiteral res; res.tipo = new Tipo(Tipo::BOOL);
    if (esq.tipo->valor == Tipo::INT) res.valor_bool = esq.valor_int == dir.valor_int;
    else if (esq.tipo->valor == Tipo::FLOAT) res.valor_bool = esq.valor_float == dir.valor_float;
    else res.valor_bool = esq.valor_bool == dir.valor_bool;
    return res;
  }
  if (ExpressaoDiferente* op = dynamic_cast<ExpressaoDiferente*>(exp)) {
    ValorLiteral esq = avalia_expressao(op->esquerda);
    ValorLiteral dir = avalia_expressao(op->direita);
    if (esq.tipo->valor != dir.tipo->valor) {
      cerr << "ERRO SEMANTICO: Tipos incompativeis para !=" << endl; exit(1);
    }
    ValorLiteral res; res.tipo = new Tipo(Tipo::BOOL);
    if (esq.tipo->valor == Tipo::INT) res.valor_bool = esq.valor_int != dir.valor_int;
    else if (esq.tipo->valor == Tipo::FLOAT) res.valor_bool = esq.valor_float != dir.valor_float;
    else res.valor_bool = esq.valor_bool != dir.valor_bool;
    return res;
  }
  if (ExpressaoAnd* op = dynamic_cast<ExpressaoAnd*>(exp)) {
    ValorLiteral esq = avalia_expressao(op->esquerda);
    ValorLiteral dir = avalia_expressao(op->direita);
    if (esq.tipo->valor != Tipo::BOOL || dir.tipo->valor != Tipo::BOOL) {
      cerr << "ERRO SEMANTICO: Tipos incompativeis para &&" << endl; exit(1);
    }
    ValorLiteral res; res.tipo = new Tipo(Tipo::BOOL);
    res.valor_bool = esq.valor_bool && dir.valor_bool;
    return res;
  }
  if (ExpressaoOr* op = dynamic_cast<ExpressaoOr*>(exp)) {
    ValorLiteral esq = avalia_expressao(op->esquerda);
    ValorLiteral dir = avalia_expressao(op->direita);
    if (esq.tipo->valor != Tipo::BOOL || dir.tipo->valor != Tipo::BOOL) {
      cerr << "ERRO SEMANTICO: Tipos incompativeis para ||" << endl; exit(1);
    }
    ValorLiteral res; res.tipo = new Tipo(Tipo::BOOL);
    res.valor_bool = esq.valor_bool || dir.valor_bool;
    return res;
  }
  if (ExpressaoNegacao* op = dynamic_cast<ExpressaoNegacao*>(exp)) {
    ValorLiteral val = avalia_expressao(op->expressao);
    if (val.tipo->valor != Tipo::BOOL) {
      cerr << "ERRO SEMANTICO: Tipos incompativeis para !" << endl; exit(1);
    }
    ValorLiteral res; res.tipo = new Tipo(Tipo::BOOL);
    res.valor_bool = !val.valor_bool;
    return res;
  }
  if (ExpressaoMenosUnario* op = dynamic_cast<ExpressaoMenosUnario*>(exp)) {
    ValorLiteral val = avalia_expressao(op->expressao);
    if (val.tipo->valor == Tipo::BOOL) {
      cerr << "ERRO SEMANTICO: Tipos incompativeis para unario -" << endl; exit(1);
    }
    ValorLiteral res; res.tipo = val.tipo;
    if (res.tipo->valor == Tipo::INT) res.valor_int = -val.valor_int;
    else res.valor_float = -val.valor_float;
    return res;
  }
  if (ExpressaoCast* op = dynamic_cast<ExpressaoCast*>(exp)) {
    ValorLiteral val = avalia_expressao(op->expressao);
    ValorLiteral res; res.tipo = op->tipo;
    if (res.tipo->valor == Tipo::INT) {
      if (val.tipo->valor == Tipo::INT) res.valor_int = val.valor_int;
      else if (val.tipo->valor == Tipo::FLOAT) res.valor_int = (int)val.valor_float;
      else res.valor_int = val.valor_bool ? 1 : 0;
    } else if (res.tipo->valor == Tipo::FLOAT) {
      if (val.tipo->valor == Tipo::INT) res.valor_float = (float)val.valor_int;
      else if (val.tipo->valor == Tipo::FLOAT) res.valor_float = val.valor_float;
      else res.valor_float = val.valor_bool ? 1.0f : 0.0f;
    } else if (res.tipo->valor == Tipo::BOOL) {
      if (val.tipo->valor == Tipo::INT) res.valor_bool = val.valor_int != 0;
      else if (val.tipo->valor == Tipo::FLOAT) res.valor_bool = val.valor_float != 0.0f;
      else res.valor_bool = val.valor_bool;
    }
    return res;
  }
  
  if (dynamic_cast<ExpressaoChamada*>(exp)) {
    ValorLiteral res;
    res.tipo = new Tipo(Tipo::INT);
    res.valor_int = 0;
    return res;
  }
  
  return nulo;
}

void Analisador::executa_comando(Comando* cmd) {
  if (is_returning) return;
  if (cmd == NULL) return;

  if (ComandoLista* lista = dynamic_cast<ComandoLista*>(cmd)) {
    entra_escopo();
    for (int i = 0; i < lista->lista_comandos.size(); ++i) {
      executa_comando(lista->lista_comandos[i]);
      if (is_returning) break;
    }
    sai_escopo();
  } else if (ComandoDeclaracao* decl = dynamic_cast<ComandoDeclaracao*>(cmd)) {
    declara_var(decl->variavel->nome->nome, decl->variavel->tipo);
  } else if (ComandoAtribuicao* attr = dynamic_cast<ComandoAtribuicao*>(cmd)) {
    ValorLiteral val = avalia_expressao(attr->direita);
    atribui_var(attr->esquerda->nome, val);
  } else if (ComandoIf* cif = dynamic_cast<ComandoIf*>(cmd)) {
    ValorLiteral cond = avalia_expressao(cif->condicao);
    if (cond.tipo->valor != Tipo::BOOL) {
      cerr << "ERRO SEMANTICO: Condicao do IF nao booleana" << endl; exit(1);
    }
    if (cond.valor_bool) {
      executa_comando(cif->bloco_if);
    } else if (cif->bloco_else != NULL) {
      executa_comando(cif->bloco_else);
    }
  } else if (ComandoWhile* cwh = dynamic_cast<ComandoWhile*>(cmd)) {
    while (true) {
      ValorLiteral cond = avalia_expressao(cwh->condicao);
      if (cond.tipo->valor != Tipo::BOOL) {
        cerr << "ERRO SEMANTICO: Condicao do WHILE nao booleana" << endl; exit(1);
      }
      if (!cond.valor_bool) break;
      executa_comando(cwh->bloco);
      if (is_returning) break;
    }
  } else if (ComandoRetorno* ret = dynamic_cast<ComandoRetorno*>(cmd)) {
    is_returning = true;
    if (ret->expressao != NULL) {
      valor_retorno = avalia_expressao(ret->expressao);
      ultimo_atribuido = valor_retorno;
    }
  }
}

int Analisador::calcula_retorno(Funcao *f, const vector<ValorLiteral> &params) {
  is_returning = false;
  ultimo_atribuido.tipo = NULL;
  entra_escopo();
  
  if (f->parametros.size() != params.size()) {
    cerr << "ERRO SEMANTICO: Numero incorreto de parametros passados" << endl;
    exit(1);
  }
  
  for (int i = 0; i < params.size(); ++i) {
    if (f->parametros[i]->tipo->valor != params[i].tipo->valor) {
      cerr << "ERRO SEMANTICO: Tipo do parametro " << f->parametros[i]->nome->nome << " incompativel" << endl;
      exit(1);
    }
    declara_var(f->parametros[i]->nome->nome, params[i].tipo);
    atribui_var(f->parametros[i]->nome->nome, params[i]);
  }
  
  cerr << "Executando " << f->comandos.size() << " comandos." << endl;
  for (int i = 0; i < f->comandos.size(); ++i) {
    cerr << "Executando comando " << i << endl;
    executa_comando(f->comandos[i]);
    if (is_returning) {
      cerr << "Retorno acionado no comando " << i << endl;
      break;
    }
  }
  
  sai_escopo();
  
  ValorLiteral output = ultimo_atribuido;
  if (is_returning && valor_retorno.tipo != NULL) {
    cerr << "Usando valor_retorno com tipo: " << valor_retorno.tipo->nome() << endl;
    output = valor_retorno;
  }
  
  if (output.tipo == NULL) {
    cerr << "Erro: output.tipo eh NULL!" << endl;
    return 0;
  }
  
  cerr << "Calculado com sucesso. Output tipo: " << output.tipo->nome() << endl;
  
  if (output.tipo->valor == Tipo::BOOL) {
    cout << (output.valor_bool ? "true" : "false") << endl;
  } else if (output.tipo->valor == Tipo::FLOAT) {
    cout << fixed << setprecision(2) << output.valor_float << endl;
  } else {
    cout << output.valor_int << endl;
  }
  
  return 0;
}
