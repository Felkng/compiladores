#ifndef _ANALISADOR_HPP_
#define _ANALISADOR_HPP_
#include "Funcao.hpp"
#include "ValorLiteral.hpp"
#include "ComandoIf.hpp"
#include "ComandoWhile.hpp"
#include "ComandoAtribuicao.hpp"
#include "ComandoDeclaracao.hpp"
#include "ComandoLista.hpp"
#include "ComandoRetorno.hpp"
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

#include <vector>
#include <map>
#include <string>

using namespace std;

class Analisador {
private:
  vector<map<string, ValorLiteral>> escopos;
  ValorLiteral ultimo_atribuido;
  bool is_returning;
  ValorLiteral valor_retorno;

  void entra_escopo();
  void sai_escopo();
  void declara_var(string nome, Tipo* tipo);
  void atribui_var(string nome, ValorLiteral val);
  ValorLiteral le_var(string nome);

  void executa_comando(Comando* cmd);
  ValorLiteral avalia_expressao(Expressao* exp);

public:
  Analisador();
  int calcula_retorno(Funcao *f, const vector<ValorLiteral> &params);
};
  
#endif
