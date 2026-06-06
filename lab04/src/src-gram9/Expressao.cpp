#include "Expressao.hpp"
#include "ExpressaoDivisao.hpp"
#include "ExpressaoIgualdade.hpp"
#include "ExpressaoMenor.hpp"
#include "ExpressaoMod.hpp"
#include "ExpressaoMultiplicacao.hpp"
#include "ExpressaoNegacao.hpp"
#include "ExpressaoSoma.hpp"
#include "ExpressaoSubtracao.hpp"
#include "ExpressaoValor.hpp"
#include "ExpressaoVariavel.hpp"
#include "ExpressaoMaior.hpp"
#include "ExpressaoMaiorIgual.hpp"
#include "ExpressaoMenorIgual.hpp"
#include "ExpressaoDiferente.hpp"
#include "ExpressaoAnd.hpp"
#include "ExpressaoOr.hpp"
#include "ExpressaoCast.hpp"
#include "ExpressaoChamada.hpp"
#include "ExpressaoMenosUnario.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

Expressao* Expressao::extrai_expressao(No_arv_parse* no) {
  if (no == NULL) return NULL;

  switch(no->regra) {
  case 45: case 47: case 49: case 56: case 59: case 63: case 66: case 75: case 80:
    // Fall-through rules
    return extrai_expressao(no->filhos[0]);
  case 46: { // ExprOr -> ExprOr PIPEPIPE ExprAnd
    ExpressaoOr* res = new ExpressaoOr();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 48: { // ExprAnd -> ExprAnd AMPAMP ExprCmp
    ExpressaoAnd* res = new ExpressaoAnd();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 50: { // ExprCmp -> ExprAdd EQEQ ExprAdd
    ExpressaoIgualdade* res = new ExpressaoIgualdade();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 51: { // ExprCmp -> ExprAdd BANGEQ ExprAdd
    ExpressaoDiferente* res = new ExpressaoDiferente();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 52: { // ExprCmp -> ExprAdd LT ExprAdd
    ExpressaoMenor* res = new ExpressaoMenor();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 53: { // ExprCmp -> ExprAdd LE ExprAdd
    ExpressaoMenorIgual* res = new ExpressaoMenorIgual();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 54: { // ExprCmp -> ExprAdd GT ExprAdd
    ExpressaoMaior* res = new ExpressaoMaior();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 55: { // ExprCmp -> ExprAdd GE ExprAdd
    ExpressaoMaiorIgual* res = new ExpressaoMaiorIgual();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 57: { // ExprAdd -> ExprAdd PLUS ExprMul
    ExpressaoSoma* res = new ExpressaoSoma();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 58: { // ExprAdd -> ExprAdd MINUS ExprMul
    ExpressaoSubtracao* res = new ExpressaoSubtracao();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 60: { // ExprMul -> ExprMul STAR ExprUnary
    ExpressaoMultiplicacao* res = new ExpressaoMultiplicacao();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 61: { // ExprMul -> ExprMul SLASH ExprUnary
    ExpressaoDivisao* res = new ExpressaoDivisao();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 62: { // ExprMul -> ExprMul PERCENT ExprUnary
    ExpressaoMod* res = new ExpressaoMod();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 64: { // ExprUnary -> BANG ExprUnary
    ExpressaoNegacao* res = new ExpressaoNegacao();
    res->expressao = extrai_expressao(no->filhos[1]);
    return res;
  }
  case 65: { // ExprUnary -> MINUS ExprUnary
    ExpressaoMenosUnario* res = new ExpressaoMenosUnario();
    res->expressao = extrai_expressao(no->filhos[1]);
    return res;
  }
  case 67: { // ExprPrimary -> ExprPrimary DOT ID
    // Not needed for this subset but we provide a dummy
    return extrai_expressao(no->filhos[0]);
  }
  case 68: { // ExprPrimary -> ExprPrimary KW_AS Type
    ExpressaoCast* res = new ExpressaoCast();
    res->expressao = extrai_expressao(no->filhos[0]);
    res->tipo = Tipo::extrai_Tipo(no->filhos[2]);
    return res;
  }
  case 69: { // ExprPrimary -> ExprPrimary LBRACKET Expr RBRACKET
    // Array access
    return extrai_expressao(no->filhos[0]);
  }
  case 70: { // ExprPrimary -> LPAREN Expr RPAREN
    return extrai_expressao(no->filhos[1]);
  }
  case 71: { // ExprPrimary -> ID
    ExpressaoVariavel* res = new ExpressaoVariavel();
    res->nome = ID::extrai_ID(no->filhos[0]);
    return res;
  }
  case 72: // LIT_INT_DEC
  case 73: { // LIT_FLOAT
    ExpressaoValor* res = new ExpressaoValor();
    res->valor = ValorLiteral::extrai_valor_literal(no->filhos[0]);
    return res;
  }
  case 74: { // LIT_STRING
    return NULL; // Not implemented
  }
  case 76: { // Call -> ID LPAREN Args RPAREN
    ExpressaoChamada* res = new ExpressaoChamada();
    res->nome = ID::extrai_ID(no->filhos[0]);
    // Extract Args (filhos[2])
    No_arv_parse* args_node = no->filhos[2];
    if (args_node->regra == 77) { // Args -> ArgList
      No_arv_parse* arglist = args_node->filhos[0];
      while (arglist != NULL && arglist->regra == 79) { // ArgList COMMA Expr
        res->argumentos.insert(res->argumentos.begin(), extrai_expressao(arglist->filhos[2]));
        arglist = arglist->filhos[0];
      }
      if (arglist != NULL && arglist->regra == 80) { // ArgList -> Expr
        res->argumentos.insert(res->argumentos.begin(), extrai_expressao(arglist->filhos[0]));
      }
    }
    return res;
  }
  default:
    return NULL;
  }
}

void Expressao::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "Expressao generica" << endl;
}
