#include <algorithm>
#include<vector>
#include<string>
#include<iostream>
#include <fstream>   
#include<sstream>
#include<map>
#include<stack>
using namespace std;

#include "Gramatica.hpp"
#include "TabelaLR1.hpp"
#include "Arvore.hpp"
#include "Parser.hpp"
#include "src-gram9/Funcao.hpp"
#include "Frame/FrameFuncao.hpp"
#include "TradutorRI.hpp"
#include "Tree/Stm.hpp"

int main(int argc, char * argv[]) {
  if (argc != 3 && argc != 1) {
    cerr << "Parametros nomes dos arquivos: 1) csv com gramática e 2) csv com tabela LR1" << endl;
    return 1;
  }
  string nome_gramatica, nome_tab_lr1;
  if (argc == 1) {
    //cerr << "Valores padrao utilizados: gramatica.conf e tabela_lr1.conf" << endl;
    nome_gramatica = string("gramatica.conf");
    nome_tab_lr1 = string("tabela_lr1.conf");
  } else {
    nome_gramatica = string(argv[1]);
    nome_tab_lr1 = string(argv[2]);
  }

  ifstream arq_gramatica(nome_gramatica);
  ifstream arq_tabela_lr1(nome_tab_lr1);
  if (arq_tabela_lr1.fail() || arq_gramatica.fail()) {
    cerr << "Falha ao abrir arquivos: " << 
      ((arq_gramatica.fail()) ? nome_gramatica : "") << ", " << 
      ((arq_tabela_lr1.fail()) ? nome_tab_lr1 : "") << endl;
    return 1;    
  }
  Parser parser(arq_gramatica, arq_tabela_lr1);

  Arvore_parse arv = parser.executa_parse(cin);
  Funcao* func = Funcao::extrai_funcao(arv.raiz);
  if (!func) {
    cerr << "Erro: Nao foi possivel extrair a funcao da arvore!" << endl;
    return 1;
  }

  FrameFuncao* frame = FrameFuncao::gera_frame_de_funcao(func);
  if (!frame) {
    cerr << "Erro: Nao foi possivel gerar o frame da funcao!" << endl;
    return 1;
  }

  TradutorRI tradutor;
  Stm* representacao_funcao = tradutor.traduz_funcao(func, frame);
  if (representacao_funcao) {
    representacao_funcao->print();
    delete representacao_funcao;
  }
  delete frame;
  delete func;

  return 0;
}
