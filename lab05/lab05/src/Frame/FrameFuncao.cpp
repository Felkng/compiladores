#include "FrameFuncao.hpp"
#include "FrameAcesso.hpp"
#include "FrameAcessoNoFrame.hpp"
#include "FrameAcessoTemp.hpp"

#include "../src-gram9/Comando.hpp"
#include "../src-gram9/ComandoDeclaracao.hpp"
#include "../src-gram9/ComandoLista.hpp"
#include "../src-gram9/ComandoIf.hpp"
#include "../src-gram9/ComandoWhile.hpp"
#include "../src-gram9/ComandoAtribuicao.hpp"
#include "../src-gram9/ComandoRetorno.hpp"
#include "../src-gram9/Expressao.hpp"
#include "../src-gram9/ExpressaoVariavel.hpp"
#include "../src-gram9/ExpressaoChamada.hpp"
#include "../src-gram9/ExpressaoValor.hpp"
#include "../src-gram9/ExpressaoSoma.hpp"
#include "../src-gram9/ExpressaoSubtracao.hpp"
#include "../src-gram9/ExpressaoMultiplicacao.hpp"
#include "../src-gram9/ExpressaoDivisao.hpp"
#include "../src-gram9/ExpressaoMod.hpp"
#include "../src-gram9/ExpressaoMenor.hpp"
#include "../src-gram9/ExpressaoMaior.hpp"
#include "../src-gram9/ExpressaoMenorIgual.hpp"
#include "../src-gram9/ExpressaoMaiorIgual.hpp"
#include "../src-gram9/ExpressaoIgualdade.hpp"
#include "../src-gram9/ExpressaoDiferente.hpp"
#include "../src-gram9/ExpressaoAnd.hpp"
#include "../src-gram9/ExpressaoOr.hpp"
#include "../src-gram9/ExpressaoNegacao.hpp"
#include "../src-gram9/ExpressaoMenosUnario.hpp"
#include "../src-gram9/ExpressaoCast.hpp"

#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

// Helper to find the maximum number of arguments in any function call
static void coleta_max_param_saida(Expressao* exp, int& max_param_saida) {
  if (exp == NULL) return;

  if (ExpressaoChamada* ecall = dynamic_cast<ExpressaoChamada*>(exp)) {
    int nargs = ecall->argumentos.size();
    if (nargs > max_param_saida) {
      max_param_saida = nargs;
    }
    for (Expressao* arg : ecall->argumentos) {
      coleta_max_param_saida(arg, max_param_saida);
    }
    return;
  }
  if (ExpressaoNegacao* eneg = dynamic_cast<ExpressaoNegacao*>(exp)) {
    coleta_max_param_saida(eneg->expressao, max_param_saida);
    return;
  }
  if (ExpressaoMenosUnario* emen = dynamic_cast<ExpressaoMenosUnario*>(exp)) {
    coleta_max_param_saida(emen->expressao, max_param_saida);
    return;
  }
  if (ExpressaoCast* ecast = dynamic_cast<ExpressaoCast*>(exp)) {
    coleta_max_param_saida(ecast->expressao, max_param_saida);
    return;
  }

  // Binary expressions
  if (ExpressaoSoma* es = dynamic_cast<ExpressaoSoma*>(exp)) {
    coleta_max_param_saida(es->esquerda, max_param_saida);
    coleta_max_param_saida(es->direita, max_param_saida);
    return;
  }
  if (ExpressaoSubtracao* es = dynamic_cast<ExpressaoSubtracao*>(exp)) {
    coleta_max_param_saida(es->esquerda, max_param_saida);
    coleta_max_param_saida(es->direita, max_param_saida);
    return;
  }
  if (ExpressaoMultiplicacao* em = dynamic_cast<ExpressaoMultiplicacao*>(exp)) {
    coleta_max_param_saida(em->esquerda, max_param_saida);
    coleta_max_param_saida(em->direita, max_param_saida);
    return;
  }
  if (ExpressaoDivisao* ed = dynamic_cast<ExpressaoDivisao*>(exp)) {
    coleta_max_param_saida(ed->esquerda, max_param_saida);
    coleta_max_param_saida(ed->direita, max_param_saida);
    return;
  }
  if (ExpressaoMod* em = dynamic_cast<ExpressaoMod*>(exp)) {
    coleta_max_param_saida(em->esquerda, max_param_saida);
    coleta_max_param_saida(em->direita, max_param_saida);
    return;
  }
  if (ExpressaoMenor* em = dynamic_cast<ExpressaoMenor*>(exp)) {
    coleta_max_param_saida(em->esquerda, max_param_saida);
    coleta_max_param_saida(em->direita, max_param_saida);
    return;
  }
  if (ExpressaoMaior* em = dynamic_cast<ExpressaoMaior*>(exp)) {
    coleta_max_param_saida(em->esquerda, max_param_saida);
    coleta_max_param_saida(em->direita, max_param_saida);
    return;
  }
  if (ExpressaoMenorIgual* em = dynamic_cast<ExpressaoMenorIgual*>(exp)) {
    coleta_max_param_saida(em->esquerda, max_param_saida);
    coleta_max_param_saida(em->direita, max_param_saida);
    return;
  }
  if (ExpressaoMaiorIgual* em = dynamic_cast<ExpressaoMaiorIgual*>(exp)) {
    coleta_max_param_saida(em->esquerda, max_param_saida);
    coleta_max_param_saida(em->direita, max_param_saida);
    return;
  }
  if (ExpressaoIgualdade* em = dynamic_cast<ExpressaoIgualdade*>(exp)) {
    coleta_max_param_saida(em->esquerda, max_param_saida);
    coleta_max_param_saida(em->direita, max_param_saida);
    return;
  }
  if (ExpressaoDiferente* em = dynamic_cast<ExpressaoDiferente*>(exp)) {
    coleta_max_param_saida(em->esquerda, max_param_saida);
    coleta_max_param_saida(em->direita, max_param_saida);
    return;
  }
  if (ExpressaoAnd* em = dynamic_cast<ExpressaoAnd*>(exp)) {
    coleta_max_param_saida(em->esquerda, max_param_saida);
    coleta_max_param_saida(em->direita, max_param_saida);
    return;
  }
  if (ExpressaoOr* em = dynamic_cast<ExpressaoOr*>(exp)) {
    coleta_max_param_saida(em->esquerda, max_param_saida);
    coleta_max_param_saida(em->direita, max_param_saida);
    return;
  }
}

static Variavel* lookup_variable(const string& nome, const vector<map<string, Variavel*>>& scopes) {
  for (int i = (int)scopes.size() - 1; i >= 0; --i) {
    auto it = scopes[i].find(nome);
    if (it != scopes[i].end()) {
      return it->second;
    }
  }
  return NULL;
}

// Recursive expression visitor to find all ExpressaoVariavel usages and resolve them
static void coleta_e_resolve_usos(
  Expressao* exp,
  bool in_call_argument,
  const vector<map<string, Variavel*>>& scopes,
  vector<pair<ExpressaoVariavel*, bool>>& usos,
  map<ExpressaoVariavel*, Variavel*>& resolved_vars
) {
  if (exp == NULL) return;

  if (ExpressaoVariavel* evar = dynamic_cast<ExpressaoVariavel*>(exp)) {
    if (evar->nome && evar->nome->nome != "true" && evar->nome->nome != "false") {
      Variavel* decl = lookup_variable(evar->nome->nome, scopes);
      if (decl) {
        resolved_vars[evar] = decl;
        usos.push_back({evar, in_call_argument});
      }
    }
    return;
  }
  if (ExpressaoChamada* ecall = dynamic_cast<ExpressaoChamada*>(exp)) {
    for (Expressao* arg : ecall->argumentos) {
      coleta_e_resolve_usos(arg, true, scopes, usos, resolved_vars);
    }
    return;
  }
  if (ExpressaoNegacao* eneg = dynamic_cast<ExpressaoNegacao*>(exp)) {
    coleta_e_resolve_usos(eneg->expressao, in_call_argument, scopes, usos, resolved_vars);
    return;
  }
  if (ExpressaoMenosUnario* emen = dynamic_cast<ExpressaoMenosUnario*>(exp)) {
    coleta_e_resolve_usos(emen->expressao, in_call_argument, scopes, usos, resolved_vars);
    return;
  }
  if (ExpressaoCast* ecast = dynamic_cast<ExpressaoCast*>(exp)) {
    coleta_e_resolve_usos(ecast->expressao, in_call_argument, scopes, usos, resolved_vars);
    return;
  }

  // Binary expressions
  if (ExpressaoSoma* es = dynamic_cast<ExpressaoSoma*>(exp)) {
    coleta_e_resolve_usos(es->esquerda, in_call_argument, scopes, usos, resolved_vars);
    coleta_e_resolve_usos(es->direita, in_call_argument, scopes, usos, resolved_vars);
    return;
  }
  if (ExpressaoSubtracao* es = dynamic_cast<ExpressaoSubtracao*>(exp)) {
    coleta_e_resolve_usos(es->esquerda, in_call_argument, scopes, usos, resolved_vars);
    coleta_e_resolve_usos(es->direita, in_call_argument, scopes, usos, resolved_vars);
    return;
  }
  if (ExpressaoMultiplicacao* em = dynamic_cast<ExpressaoMultiplicacao*>(exp)) {
    coleta_e_resolve_usos(em->esquerda, in_call_argument, scopes, usos, resolved_vars);
    coleta_e_resolve_usos(em->direita, in_call_argument, scopes, usos, resolved_vars);
    return;
  }
  if (ExpressaoDivisao* ed = dynamic_cast<ExpressaoDivisao*>(exp)) {
    coleta_e_resolve_usos(ed->esquerda, in_call_argument, scopes, usos, resolved_vars);
    coleta_e_resolve_usos(ed->direita, in_call_argument, scopes, usos, resolved_vars);
    return;
  }
  if (ExpressaoMod* em = dynamic_cast<ExpressaoMod*>(exp)) {
    coleta_e_resolve_usos(em->esquerda, in_call_argument, scopes, usos, resolved_vars);
    coleta_e_resolve_usos(em->direita, in_call_argument, scopes, usos, resolved_vars);
    return;
  }
  if (ExpressaoMenor* em = dynamic_cast<ExpressaoMenor*>(exp)) {
    coleta_e_resolve_usos(em->esquerda, in_call_argument, scopes, usos, resolved_vars);
    coleta_e_resolve_usos(em->direita, in_call_argument, scopes, usos, resolved_vars);
    return;
  }
  if (ExpressaoMaior* em = dynamic_cast<ExpressaoMaior*>(exp)) {
    coleta_e_resolve_usos(em->esquerda, in_call_argument, scopes, usos, resolved_vars);
    coleta_e_resolve_usos(em->direita, in_call_argument, scopes, usos, resolved_vars);
    return;
  }
  if (ExpressaoMenorIgual* em = dynamic_cast<ExpressaoMenorIgual*>(exp)) {
    coleta_e_resolve_usos(em->esquerda, in_call_argument, scopes, usos, resolved_vars);
    coleta_e_resolve_usos(em->direita, in_call_argument, scopes, usos, resolved_vars);
    return;
  }
  if (ExpressaoMaiorIgual* em = dynamic_cast<ExpressaoMaiorIgual*>(exp)) {
    coleta_e_resolve_usos(em->esquerda, in_call_argument, scopes, usos, resolved_vars);
    coleta_e_resolve_usos(em->direita, in_call_argument, scopes, usos, resolved_vars);
    return;
  }
  if (ExpressaoIgualdade* em = dynamic_cast<ExpressaoIgualdade*>(exp)) {
    coleta_e_resolve_usos(em->esquerda, in_call_argument, scopes, usos, resolved_vars);
    coleta_e_resolve_usos(em->direita, in_call_argument, scopes, usos, resolved_vars);
    return;
  }
  if (ExpressaoDiferente* em = dynamic_cast<ExpressaoDiferente*>(exp)) {
    coleta_e_resolve_usos(em->esquerda, in_call_argument, scopes, usos, resolved_vars);
    coleta_e_resolve_usos(em->direita, in_call_argument, scopes, usos, resolved_vars);
    return;
  }
  if (ExpressaoAnd* em = dynamic_cast<ExpressaoAnd*>(exp)) {
    coleta_e_resolve_usos(em->esquerda, in_call_argument, scopes, usos, resolved_vars);
    coleta_e_resolve_usos(em->direita, in_call_argument, scopes, usos, resolved_vars);
    return;
  }
  if (ExpressaoOr* em = dynamic_cast<ExpressaoOr*>(exp)) {
    coleta_e_resolve_usos(em->esquerda, in_call_argument, scopes, usos, resolved_vars);
    coleta_e_resolve_usos(em->direita, in_call_argument, scopes, usos, resolved_vars);
    return;
  }
}

struct Resolvidos {
  vector<Variavel*> local_vars;
};

static void resolve_scopes(
  const vector<Comando*>& cmds,
  vector<map<string, Variavel*>>& scopes,
  Resolvidos& res,
  int& max_param_saida,
  vector<pair<ExpressaoVariavel*, bool>>& usos,
  map<ExpressaoVariavel*, Variavel*>& resolved_vars
) {
  for (Comando* cmd : cmds) {
    if (cmd == NULL) continue;

    if (ComandoLista* lista = dynamic_cast<ComandoLista*>(cmd)) {
      if (lista->is_block_scope) {
        scopes.push_back(map<string, Variavel*>());
      }
      resolve_scopes(lista->lista_comandos, scopes, res, max_param_saida, usos, resolved_vars);
      if (lista->is_block_scope) {
        scopes.pop_back();
      }
    }
    else if (ComandoDeclaracao* decl = dynamic_cast<ComandoDeclaracao*>(cmd)) {
      if (decl->variavel && decl->variavel->nome) {
        scopes.back()[decl->variavel->nome->nome] = decl->variavel;
        res.local_vars.push_back(decl->variavel);
      }
    }
    else if (ComandoAtribuicao* attr = dynamic_cast<ComandoAtribuicao*>(cmd)) {
      coleta_max_param_saida(attr->direita, max_param_saida);
      coleta_e_resolve_usos(attr->direita, false, scopes, usos, resolved_vars);
    }
    else if (ComandoIf* cif = dynamic_cast<ComandoIf*>(cmd)) {
      coleta_max_param_saida(cif->condicao, max_param_saida);
      coleta_e_resolve_usos(cif->condicao, false, scopes, usos, resolved_vars);
      if (cif->bloco_if) {
        vector<Comando*> tmp; tmp.push_back(cif->bloco_if);
        resolve_scopes(tmp, scopes, res, max_param_saida, usos, resolved_vars);
      }
      if (cif->bloco_else) {
        vector<Comando*> tmp; tmp.push_back(cif->bloco_else);
        resolve_scopes(tmp, scopes, res, max_param_saida, usos, resolved_vars);
      }
    }
    else if (ComandoWhile* cwh = dynamic_cast<ComandoWhile*>(cmd)) {
      coleta_max_param_saida(cwh->condicao, max_param_saida);
      coleta_e_resolve_usos(cwh->condicao, false, scopes, usos, resolved_vars);
      if (cwh->bloco) {
        vector<Comando*> tmp; tmp.push_back(cwh->bloco);
        resolve_scopes(tmp, scopes, res, max_param_saida, usos, resolved_vars);
      }
    }
    else if (ComandoRetorno* ret = dynamic_cast<ComandoRetorno*>(cmd)) {
      coleta_max_param_saida(ret->expressao, max_param_saida);
      coleta_e_resolve_usos(ret->expressao, false, scopes, usos, resolved_vars);
    }
  }
}

FrameFuncao::FrameFuncao() { }

FrameFuncao* FrameFuncao::gera_frame_de_funcao(Funcao* fun) {
  FrameFuncao* ff = new FrameFuncao();
  ff->n_param_entrada = fun->parametros.size();
  
  vector<map<string, Variavel*>> scopes;
  map<string, Variavel*> param_scope;
  for (Variavel* p : fun->parametros) {
    param_scope[p->nome->nome] = p;
  }
  scopes.push_back(param_scope);

  Resolvidos res;
  int max_param_saida = 0;
  vector<pair<ExpressaoVariavel*, bool>> usos;
  map<ExpressaoVariavel*, Variavel*> resolved_vars;

  resolve_scopes(fun->comandos, scopes, res, max_param_saida, usos, resolved_vars);

  ff->n_maximo_param_saida = max_param_saida;

  // Initialize accesses for parameters (always on the caller's frame, FP+8, FP+16...)
  map<Variavel*, FrameAcesso*> acessos;
  for (size_t i = 0; i < fun->parametros.size(); ++i) {
    Variavel* p = fun->parametros[i];
    FrameAcessoNoFrame* acc = new FrameAcessoNoFrame();
    acc->posicao_no_frame = 8 * (i + 1);
    acessos[p] = acc;
  }

  // Identify local variables that are used inside any function call argument
  set<Variavel*> local_vars_in_call_args;
  for (auto& p : usos) {
    ExpressaoVariavel* evar = p.first;
    bool in_call_arg = p.second;
    if (in_call_arg) {
      Variavel* decl = resolved_vars[evar];
      if (decl) {
        local_vars_in_call_args.insert(decl);
      }
    }
  }

  int n_variaveis_no_frame = 0;
  int n_pseudo_registradores = 0;

  for (Variavel* v : res.local_vars) {
    // Only allocate access if not already allocated (handles duplicates if any, though pointers are unique)
    if (acessos.count(v)) continue;

    if (local_vars_in_call_args.count(v)) {
      FrameAcessoNoFrame* acc = new FrameAcessoNoFrame();
      acc->posicao_no_frame = -40 - 8 * n_variaveis_no_frame;
      n_variaveis_no_frame++;
      acessos[v] = acc;
    } else {
      FrameAcessoTemp* acc = new FrameAcessoTemp();
      acc->id = 1 + n_pseudo_registradores;
      n_pseudo_registradores++;
      acessos[v] = acc;
    }
  }

  ff->n_variaveis_no_frame = n_variaveis_no_frame;
  ff->n_pseudo_registradores = n_pseudo_registradores;
  ff->tamanho_frame = 40 + 8 * n_variaveis_no_frame;

  // Populate ExpressaoVariavel uses with their access object
  for (auto& p : resolved_vars) {
    ExpressaoVariavel* evar = p.first;
    Variavel* decl = p.second;
    if (acessos.count(decl)) {
      evar->acesso = acessos[decl];
      evar->acesso_frame = acessos[decl];
    }
  }

  ff->acessos = acessos;
  return ff;
}

static void print_variable_usages(Expressao* exp) {
  if (exp == NULL) return;

  if (ExpressaoVariavel* evar = dynamic_cast<ExpressaoVariavel*>(exp)) {
    if (evar->nome && evar->nome->nome != "true" && evar->nome->nome != "false") {
      cout << "uso_var: " << evar->nome->nome << " -> ";
      if (evar->acesso_frame == NULL) {
        cout << "sem_acesso" << endl;
      } else if (FrameAcessoNoFrame* naf = dynamic_cast<FrameAcessoNoFrame*>(evar->acesso_frame)) {
        cout << "no_frame, posicao_no_frame: " << naf->posicao_no_frame << endl;
      } else if (FrameAcessoTemp* tmp = dynamic_cast<FrameAcessoTemp*>(evar->acesso_frame)) {
        cout << "em_pseudo_registrador, id: " << tmp->id << endl;
      }
    }
    return;
  }
  if (ExpressaoChamada* ecall = dynamic_cast<ExpressaoChamada*>(exp)) {
    for (Expressao* arg : ecall->argumentos) {
      print_variable_usages(arg);
    }
    return;
  }
  if (ExpressaoNegacao* eneg = dynamic_cast<ExpressaoNegacao*>(exp)) {
    print_variable_usages(eneg->expressao);
    return;
  }
  if (ExpressaoMenosUnario* emen = dynamic_cast<ExpressaoMenosUnario*>(exp)) {
    print_variable_usages(emen->expressao);
    return;
  }
  if (ExpressaoCast* ecast = dynamic_cast<ExpressaoCast*>(exp)) {
    print_variable_usages(ecast->expressao);
    return;
  }

  // Binary expressions
  if (ExpressaoSoma* es = dynamic_cast<ExpressaoSoma*>(exp)) {
    print_variable_usages(es->esquerda);
    print_variable_usages(es->direita);
    return;
  }
  if (ExpressaoSubtracao* es = dynamic_cast<ExpressaoSubtracao*>(exp)) {
    print_variable_usages(es->esquerda);
    print_variable_usages(es->direita);
    return;
  }
  if (ExpressaoMultiplicacao* em = dynamic_cast<ExpressaoMultiplicacao*>(exp)) {
    print_variable_usages(em->esquerda);
    print_variable_usages(em->direita);
    return;
  }
  if (ExpressaoDivisao* ed = dynamic_cast<ExpressaoDivisao*>(exp)) {
    print_variable_usages(ed->esquerda);
    print_variable_usages(ed->direita);
    return;
  }
  if (ExpressaoMod* em = dynamic_cast<ExpressaoMod*>(exp)) {
    print_variable_usages(em->esquerda);
    print_variable_usages(em->direita);
    return;
  }
  if (ExpressaoMenor* em = dynamic_cast<ExpressaoMenor*>(exp)) {
    print_variable_usages(em->esquerda);
    print_variable_usages(em->direita);
    return;
  }
  if (ExpressaoMaior* em = dynamic_cast<ExpressaoMaior*>(exp)) {
    print_variable_usages(em->esquerda);
    print_variable_usages(em->direita);
    return;
  }
  if (ExpressaoMenorIgual* em = dynamic_cast<ExpressaoMenorIgual*>(exp)) {
    print_variable_usages(em->esquerda);
    print_variable_usages(em->direita);
    return;
  }
  if (ExpressaoMaiorIgual* em = dynamic_cast<ExpressaoMaiorIgual*>(exp)) {
    print_variable_usages(em->esquerda);
    print_variable_usages(em->direita);
    return;
  }
  if (ExpressaoIgualdade* em = dynamic_cast<ExpressaoIgualdade*>(exp)) {
    print_variable_usages(em->esquerda);
    print_variable_usages(em->direita);
    return;
  }
  if (ExpressaoDiferente* em = dynamic_cast<ExpressaoDiferente*>(exp)) {
    print_variable_usages(em->esquerda);
    print_variable_usages(em->direita);
    return;
  }
  if (ExpressaoAnd* em = dynamic_cast<ExpressaoAnd*>(exp)) {
    print_variable_usages(em->esquerda);
    print_variable_usages(em->direita);
    return;
  }
  if (ExpressaoOr* em = dynamic_cast<ExpressaoOr*>(exp)) {
    print_variable_usages(em->esquerda);
    print_variable_usages(em->direita);
    return;
  }
}

static void print_command_variable_usages(const vector<Comando*>& cmds) {
  for (Comando* cmd : cmds) {
    if (cmd == NULL) continue;

    if (ComandoLista* lista = dynamic_cast<ComandoLista*>(cmd)) {
      print_command_variable_usages(lista->lista_comandos);
    }
    else if (ComandoAtribuicao* attr = dynamic_cast<ComandoAtribuicao*>(cmd)) {
      print_variable_usages(attr->direita);
    }
    else if (ComandoIf* cif = dynamic_cast<ComandoIf*>(cmd)) {
      print_variable_usages(cif->condicao);
      if (cif->bloco_if) {
        vector<Comando*> tmp; tmp.push_back(cif->bloco_if);
        print_command_variable_usages(tmp);
      }
      if (cif->bloco_else) {
        vector<Comando*> tmp; tmp.push_back(cif->bloco_else);
        print_command_variable_usages(tmp);
      }
    }
    else if (ComandoWhile* cwh = dynamic_cast<ComandoWhile*>(cmd)) {
      print_variable_usages(cwh->condicao);
      if (cwh->bloco) {
        vector<Comando*> tmp; tmp.push_back(cwh->bloco);
        print_command_variable_usages(tmp);
      }
    }
    else if (ComandoRetorno* ret = dynamic_cast<ComandoRetorno*>(cmd)) {
      print_variable_usages(ret->expressao);
    }
  }
}

void FrameFuncao::print_detalhes(Funcao* fun) {
  print_command_variable_usages(fun->comandos);
}
