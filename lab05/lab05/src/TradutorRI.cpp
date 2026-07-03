#include "TradutorRI.hpp"
#include <iostream>

// Include Gramática 9 AST nodes
#include "src-gram9/Comando.hpp"
#include "src-gram9/ComandoDeclaracao.hpp"
#include "src-gram9/ComandoLista.hpp"
#include "src-gram9/ComandoIf.hpp"
#include "src-gram9/ComandoWhile.hpp"
#include "src-gram9/ComandoAtribuicao.hpp"
#include "src-gram9/ComandoRetorno.hpp"
#include "src-gram9/Expressao.hpp"
#include "src-gram9/ExpressaoVariavel.hpp"
#include "src-gram9/ExpressaoChamada.hpp"
#include "src-gram9/ExpressaoValor.hpp"
#include "src-gram9/ExpressaoSoma.hpp"
#include "src-gram9/ExpressaoSubtracao.hpp"
#include "src-gram9/ExpressaoMultiplicacao.hpp"
#include "src-gram9/ExpressaoDivisao.hpp"
#include "src-gram9/ExpressaoMod.hpp"
#include "src-gram9/ExpressaoMenor.hpp"
#include "src-gram9/ExpressaoMaior.hpp"
#include "src-gram9/ExpressaoMenorIgual.hpp"
#include "src-gram9/ExpressaoMaiorIgual.hpp"
#include "src-gram9/ExpressaoIgualdade.hpp"
#include "src-gram9/ExpressaoDiferente.hpp"
#include "src-gram9/ExpressaoAnd.hpp"
#include "src-gram9/ExpressaoOr.hpp"
#include "src-gram9/ExpressaoNegacao.hpp"
#include "src-gram9/ExpressaoMenosUnario.hpp"
#include "src-gram9/ExpressaoCast.hpp"

// Include IR node classes
#include "Tree/ExpBinop.hpp"
#include "Tree/ExpCall.hpp"
#include "Tree/ExpConst.hpp"
#include "Tree/ExpEseq.hpp"
#include "Tree/ExpMem.hpp"
#include "Tree/ExpName.hpp"
#include "Tree/ExpTemp.hpp"
#include "Tree/ExpTempFramePointer.hpp"
#include "Tree/StmCJump.hpp"
#include "Tree/StmExp.hpp"
#include "Tree/StmJump.hpp"
#include "Tree/StmLabel.hpp"
#include "Tree/StmMove.hpp"
#include "Tree/StmSeq.hpp"

// Include IR operator classes
#include "Tree/OperadorSoma.hpp"
#include "Tree/OperadorSubtracao.hpp"
#include "Tree/OperadorMultiplicacao.hpp"
#include "Tree/OperadorDivisao.hpp"
#include "Tree/OperadorMod.hpp"
#include "Tree/OperadorMenor.hpp"
#include "Tree/OperadorMaior.hpp"
#include "Tree/OperadorMenorIgual.hpp"
#include "Tree/OperadorMaiorIgual.hpp"
#include "Tree/OperadorIgualdade.hpp"
#include "Tree/OperadorDiferente.hpp"
#include "Tree/OperadorAnd.hpp"
#include "Tree/OperadorOr.hpp"

// Include Frame access classes
#include "Frame/FrameAcesso.hpp"
#include "Frame/FrameAcessoNoFrame.hpp"
#include "Frame/FrameAcessoTemp.hpp"

using namespace std;

TradutorRI::TradutorRI() : label_counter(0) {}

string TradutorRI::gera_label() {
  return "L" + to_string(label_counter++);
}

Exp* TradutorRI::traduz_expressao(Expressao* exp, FrameFuncao* frame, vector<map<string, Variavel*>>& scopes) {
  if (exp == nullptr) return nullptr;

  if (auto eval = dynamic_cast<ExpressaoValor*>(exp)) {
    if (eval->valor && eval->valor->tipo && eval->valor->tipo->nome() == "bool") {
      return new ExpConst(eval->valor->valor_bool ? 1 : 0);
    } else if (eval->valor) {
      return new ExpConst(eval->valor->valor_int);
    }
    return new ExpConst(0);
  }

  if (auto evar = dynamic_cast<ExpressaoVariavel*>(exp)) {
    FrameAcesso* acc = evar->acesso_frame;
    if (acc == nullptr) acc = evar->acesso;

    if (acc == nullptr) {
      // Re-lookup access if not set
      Variavel* var = nullptr;
      for (int i = (int)scopes.size() - 1; i >= 0; --i) {
        if (evar->nome) {
          auto it = scopes[i].find(evar->nome->nome);
          if (it != scopes[i].end()) {
            var = it->second;
            break;
          }
        }
      }
      if (var && frame->acessos.count(var)) {
        acc = frame->acessos[var];
      }
    }

    if (acc) {
      if (auto naf = dynamic_cast<FrameAcessoNoFrame*>(acc)) {
        return new ExpMem(new ExpBinop(new OperadorSoma(), new ExpTempFramePointer(), new ExpConst(naf->posicao_no_frame)));
      } else if (auto tmp = dynamic_cast<FrameAcessoTemp*>(acc)) {
        return new ExpTemp(tmp->id);
      }
    }
    return new ExpConst(0); // fallback
  }

  if (auto ecast = dynamic_cast<ExpressaoCast*>(exp)) {
    return traduz_expressao(ecast->expressao, frame, scopes);
  }

  if (auto ecall = dynamic_cast<ExpressaoChamada*>(exp)) {
    vector<Exp*> args_ir;
    for (Expressao* arg : ecall->argumentos) {
      args_ir.push_back(traduz_expressao(arg, frame, scopes));
    }
    string fname = ecall->nome ? ecall->nome->nome : "unknown";
    return new ExpCall(new ExpName(fname), args_ir);
  }

  // Binary operations
  if (auto es = dynamic_cast<ExpressaoSoma*>(exp)) {
    return new ExpBinop(new OperadorSoma(), traduz_expressao(es->esquerda, frame, scopes), traduz_expressao(es->direita, frame, scopes));
  }
  if (auto es = dynamic_cast<ExpressaoSubtracao*>(exp)) {
    return new ExpBinop(new OperadorSubtracao(), traduz_expressao(es->esquerda, frame, scopes), traduz_expressao(es->direita, frame, scopes));
  }
  if (auto em = dynamic_cast<ExpressaoMultiplicacao*>(exp)) {
    return new ExpBinop(new OperadorMultiplicacao(), traduz_expressao(em->esquerda, frame, scopes), traduz_expressao(em->direita, frame, scopes));
  }
  if (auto ed = dynamic_cast<ExpressaoDivisao*>(exp)) {
    return new ExpBinop(new OperadorDivisao(), traduz_expressao(ed->esquerda, frame, scopes), traduz_expressao(ed->direita, frame, scopes));
  }
  if (auto em = dynamic_cast<ExpressaoMod*>(exp)) {
    return new ExpBinop(new OperadorMod(), traduz_expressao(em->esquerda, frame, scopes), traduz_expressao(em->direita, frame, scopes));
  }
  if (auto em = dynamic_cast<ExpressaoMenor*>(exp)) {
    return new ExpBinop(new OperadorMenor(), traduz_expressao(em->esquerda, frame, scopes), traduz_expressao(em->direita, frame, scopes));
  }
  if (auto em = dynamic_cast<ExpressaoMaior*>(exp)) {
    return new ExpBinop(new OperadorMaior(), traduz_expressao(em->esquerda, frame, scopes), traduz_expressao(em->direita, frame, scopes));
  }
  if (auto em = dynamic_cast<ExpressaoMenorIgual*>(exp)) {
    return new ExpBinop(new OperadorMenorIgual(), traduz_expressao(em->esquerda, frame, scopes), traduz_expressao(em->direita, frame, scopes));
  }
  if (auto em = dynamic_cast<ExpressaoMaiorIgual*>(exp)) {
    return new ExpBinop(new OperadorMaiorIgual(), traduz_expressao(em->esquerda, frame, scopes), traduz_expressao(em->direita, frame, scopes));
  }
  if (auto em = dynamic_cast<ExpressaoIgualdade*>(exp)) {
    return new ExpBinop(new OperadorIgualdade(), traduz_expressao(em->esquerda, frame, scopes), traduz_expressao(em->direita, frame, scopes));
  }
  if (auto em = dynamic_cast<ExpressaoDiferente*>(exp)) {
    return new ExpBinop(new OperadorDiferente(), traduz_expressao(em->esquerda, frame, scopes), traduz_expressao(em->direita, frame, scopes));
  }
  if (auto em = dynamic_cast<ExpressaoAnd*>(exp)) {
    return new ExpBinop(new OperadorAnd(), traduz_expressao(em->esquerda, frame, scopes), traduz_expressao(em->direita, frame, scopes));
  }
  if (auto em = dynamic_cast<ExpressaoOr*>(exp)) {
    return new ExpBinop(new OperadorOr(), traduz_expressao(em->esquerda, frame, scopes), traduz_expressao(em->direita, frame, scopes));
  }

  // Unary operations
  if (auto eneg = dynamic_cast<ExpressaoNegacao*>(exp)) {
    return new ExpBinop(new OperadorIgualdade(), traduz_expressao(eneg->expressao, frame, scopes), new ExpConst(0));
  }
  if (auto emen = dynamic_cast<ExpressaoMenosUnario*>(exp)) {
    return new ExpBinop(new OperadorSubtracao(), new ExpConst(0), traduz_expressao(emen->expressao, frame, scopes));
  }

  return nullptr;
}

Stm* TradutorRI::traduz_comando(Comando* cmd, FrameFuncao* frame, vector<map<string, Variavel*>>& scopes) {
  if (cmd == nullptr) return nullptr;

  if (auto decl = dynamic_cast<ComandoDeclaracao*>(cmd)) {
    if (decl->variavel && decl->variavel->nome) {
      scopes.back()[decl->variavel->nome->nome] = decl->variavel;
    }
    return nullptr;
  }

  if (auto attr = dynamic_cast<ComandoAtribuicao*>(cmd)) {
    Variavel* var = nullptr;
    string vname = attr->esquerda ? attr->esquerda->nome : "unknown";
    for (int i = (int)scopes.size() - 1; i >= 0; --i) {
      auto it = scopes[i].find(vname);
      if (it != scopes[i].end()) {
        var = it->second;
        break;
      }
    }
    if (var == nullptr) {
      cerr << "Erro: variavel nao declarada " << vname << endl;
      return nullptr;
    }
    FrameAcesso* acc = frame->acessos[var];
    Exp* dest = nullptr;
    if (auto naf = dynamic_cast<FrameAcessoNoFrame*>(acc)) {
      dest = new ExpMem(new ExpBinop(new OperadorSoma(), new ExpTempFramePointer(), new ExpConst(naf->posicao_no_frame)));
    } else if (auto tmp = dynamic_cast<FrameAcessoTemp*>(acc)) {
      dest = new ExpTemp(tmp->id);
    }
    Exp* orig = traduz_expressao(attr->direita, frame, scopes);
    if (dest && orig) {
      return new StmMove(dest, orig);
    }
    return nullptr;
  }

  if (auto ret = dynamic_cast<ComandoRetorno*>(cmd)) {
    Exp* orig = traduz_expressao(ret->expressao, frame, scopes);
    if (orig == nullptr) orig = new ExpConst(0);
    return new StmMove(new ExpTemp(0), orig);
  }

  if (auto lista = dynamic_cast<ComandoLista*>(cmd)) {
    if (lista->is_block_scope) {
      scopes.push_back(map<string, Variavel*>());
    }
    Stm* root = nullptr;
    for (Comando* c : lista->lista_comandos) {
      Stm* s = traduz_comando(c, frame, scopes);
      if (s == nullptr) continue;
      if (root == nullptr) {
        root = s;
      } else {
        root = new StmSeq(root, s);
      }
    }
    if (lista->is_block_scope) {
      scopes.pop_back();
    }
    return root;
  }

  if (auto cif = dynamic_cast<ComandoIf*>(cmd)) {
    Exp* cond_ir = traduz_expressao(cif->condicao, frame, scopes);
    if (cond_ir == nullptr) cond_ir = new ExpConst(0);
    string l_true = gera_label();
    string l_false = gera_label();

    if (cif->bloco_else == nullptr) {
      Stm* stm_true = traduz_comando(cif->bloco_if, frame, scopes);

      Stm* cj = new StmCJump(cond_ir, l_true, l_false);
      Stm* lbl_true = new StmLabel(l_true);
      Stm* lbl_false = new StmLabel(l_false);

      Stm* res = cj;
      res = new StmSeq(res, lbl_true);
      if (stm_true != nullptr) {
        res = new StmSeq(res, stm_true);
      }
      res = new StmSeq(res, lbl_false);
      return res;
    } else {
      Stm* stm_true = traduz_comando(cif->bloco_if, frame, scopes);
      Stm* stm_false = traduz_comando(cif->bloco_else, frame, scopes);
      string l_end = gera_label();

      Stm* cj = new StmCJump(cond_ir, l_true, l_false);
      Stm* lbl_true = new StmLabel(l_true);
      Stm* lbl_false = new StmLabel(l_false);
      Stm* lbl_end = new StmLabel(l_end);

      vector<string> alvos = { l_end };
      Stm* jmp_end = new StmJump(new ExpName(l_end), alvos);

      Stm* res = cj;
      res = new StmSeq(res, lbl_true);
      if (stm_true != nullptr) {
        res = new StmSeq(res, stm_true);
      }
      res = new StmSeq(res, jmp_end);
      res = new StmSeq(res, lbl_false);
      if (stm_false != nullptr) {
        res = new StmSeq(res, stm_false);
      }
      res = new StmSeq(res, lbl_end);
      return res;
    }
  }

  if (auto cwh = dynamic_cast<ComandoWhile*>(cmd)) {
    string l_test = gera_label();
    string l_body = gera_label();
    string l_end = gera_label();

    Exp* cond_ir = traduz_expressao(cwh->condicao, frame, scopes);
    if (cond_ir == nullptr) cond_ir = new ExpConst(0);
    Stm* stm_body = traduz_comando(cwh->bloco, frame, scopes);

    Stm* lbl_test = new StmLabel(l_test);
    Stm* cj = new StmCJump(cond_ir, l_body, l_end);
    Stm* lbl_body = new StmLabel(l_body);
    Stm* lbl_end = new StmLabel(l_end);

    vector<string> alvos = { l_test };
    Stm* jmp_test = new StmJump(new ExpName(l_test), alvos);

    Stm* res = lbl_test;
    res = new StmSeq(res, cj);
    res = new StmSeq(res, lbl_body);
    if (stm_body != nullptr) {
      res = new StmSeq(res, stm_body);
    }
    res = new StmSeq(res, jmp_test);
    res = new StmSeq(res, lbl_end);
    return res;
  }

  return nullptr;
}

Stm* TradutorRI::traduz_funcao(Funcao* func, FrameFuncao* frame) {
  vector<map<string, Variavel*>> scopes;
  map<string, Variavel*> param_scope;
  for (Variavel* p : func->parametros) {
    if (p && p->nome) {
      param_scope[p->nome->nome] = p;
    }
  }
  scopes.push_back(param_scope);

  Stm* root = nullptr;
  for (Comando* c : func->comandos) {
    Stm* s = traduz_comando(c, frame, scopes);
    if (s == nullptr) continue;
    if (root == nullptr) {
      root = s;
    } else {
      root = new StmSeq(root, s);
    }
  }
  return root;
}
