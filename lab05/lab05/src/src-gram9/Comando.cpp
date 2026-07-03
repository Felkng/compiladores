#include "Comando.hpp"
#include "ComandoAtribuicao.hpp"
#include "ComandoDeclaracao.hpp"
#include "ComandoLista.hpp"
#include "ComandoRetorno.hpp"
#include "ID.hpp"
#include "Variavel.hpp"
#include "ComandoIf.hpp"
#include "ComandoWhile.hpp"
#include <iostream>
#include "../debug-util.hpp"

vector<Comando*> Comando::extrai_lista_comandos(No_arv_parse* no) {
  // Statements -> Statements Statement | Statement |
  if (no->regra == 29) return vector<Comando*>();
  vector<Comando*> res;
  if (no->regra == 28) { // Statements -> Statement
    Comando* cmd = extrai_comando(no->filhos[0]);
    if (cmd) res.push_back(cmd);
    return res;
  }
  // Regra 27: Statements -> Statements Statement
  res = extrai_lista_comandos(no->filhos[0]);
  Comando* cmd = extrai_comando(no->filhos[1]);
  if (cmd) res.push_back(cmd);
  return res;
}

Comando* Comando::extrai_comando(No_arv_parse* no) {
  // Statement
  if (no->regra == 30 || no->regra == 31) { // let
    ComandoDeclaracao* res = new ComandoDeclaracao();
    Variavel* var = new Variavel();
    var->nome = ID::extrai_ID(no->filhos[2]);
    var->tipo = Tipo::extrai_Tipo(no->filhos[4]);
    res->variavel = var;
    if (no->regra == 30) {
      // Initializer -> EQ Expr (41) | (42)
      if (no->filhos[5]->regra == 41) {
         ComandoAtribuicao* attr = new ComandoAtribuicao();
         attr->esquerda = var->nome;
         attr->direita = Expressao::extrai_expressao(no->filhos[5]->filhos[1]);
         
         ComandoLista* cmd_list = new ComandoLista();
         cmd_list->lista_comandos.push_back(res);
         cmd_list->lista_comandos.push_back(attr);
         return cmd_list;
      }
    }
    return res;
  } else if (no->regra == 32) { // Expr EQ Expr SEMI
    ComandoAtribuicao* res = new ComandoAtribuicao();
    // left side should be ExprPrimary -> ID
    // for simplicity assume it's directly ID
    No_arv_parse* expr_esq = no->filhos[0];
    // Find ID inside expr
    while (expr_esq != NULL && expr_esq->filhos.size() > 0 && expr_esq->simb != "ID") {
       expr_esq = expr_esq->filhos[0];
    }
    if (expr_esq && expr_esq->simb == "ID") {
       res->esquerda = ID::extrai_ID(expr_esq);
    } else {
       res->esquerda = new ID();
       res->esquerda->nome = "ERRO_ESQUERDA";
    }
    res->direita = Expressao::extrai_expressao(no->filhos[2]);
    return res;
  } else if (no->regra == 38) { // Block
    ComandoLista* res = new ComandoLista();
    res->is_block_scope = true;
    res->lista_comandos = extrai_lista_comandos(no->filhos[0]->filhos[1]);
    return res;
  } else if (no->regra == 33) { // RETURN Expr SEMI
    ComandoRetorno* res = new ComandoRetorno();
    res->expressao = Expressao::extrai_expressao(no->filhos[1]);
    return res;
  } else if (no->regra == 34) { // RETURN SEMI
    ComandoRetorno* res = new ComandoRetorno();
    res->expressao = NULL;
    return res;
  } else if (no->regra == 35) { // IF
    ComandoIf* res = new ComandoIf();
    res->condicao = Expressao::extrai_expressao(no->filhos[2]);
    res->bloco_if = new ComandoLista();
    res->bloco_if->is_block_scope = true;
    res->bloco_if->lista_comandos = extrai_lista_comandos(no->filhos[4]->filhos[1]);
    if (no->filhos[5]->regra == 43) { // OptionalElse -> KW_ELSE Block
      res->bloco_else = new ComandoLista();
      res->bloco_else->is_block_scope = true;
      res->bloco_else->lista_comandos = extrai_lista_comandos(no->filhos[5]->filhos[1]->filhos[1]);
    } else {
      res->bloco_else = NULL;
    }
    return res;
  } else if (no->regra == 36) { // WHILE
    ComandoWhile* res = new ComandoWhile();
    res->condicao = Expressao::extrai_expressao(no->filhos[2]);
    res->bloco = new ComandoLista();
    res->bloco->is_block_scope = true;
    res->bloco->lista_comandos = extrai_lista_comandos(no->filhos[4]->filhos[1]);
    return res;
  }
  return NULL;
}

void Comando::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "Comando generico"<< endl;
}
