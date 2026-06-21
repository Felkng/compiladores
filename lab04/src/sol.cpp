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
#include "Funcao.hpp"
#include "FrameFuncao.hpp"


int main(int argc, char * argv[]) {
  if (argc < 3) {
    cerr << "Uso: compilador <gramatica> <tabela_lr1>" << endl;
    return 1;
  }
  string nome_gramatica = argv[1];
  string nome_tab_lr1 = argv[2];

  ifstream arq_gramatica(nome_gramatica);
  ifstream arq_tabela_lr1(nome_tab_lr1);
  if (arq_tabela_lr1.fail() || arq_gramatica.fail()) {
    cerr << "Falha ao abrir arquivos: " << 
      ((arq_gramatica.fail()) ? nome_gramatica : "") << ", " << 
      ((arq_tabela_lr1.fail()) ? nome_tab_lr1 : "") << endl;
    return 1;    
  }
  Parser parser(arq_gramatica, arq_tabela_lr1);
  // parser.tabela.debug();
  // parser.gram.debug();

  Arvore_parse arv = parser.executa_parse(cin);
  cerr << "Extraindo funcao..." << endl;
  Funcao* func = Funcao::extrai_funcao(arv.raiz);
  if (func == NULL) {
    cerr << "Erro: Nao foi possivel extrair a funcao da arvore!" << endl;
    return 1;
  }

  FrameFuncao* ff = FrameFuncao::gera_frame_de_funcao(func);
  if (ff) {
    cout << "tamanho_frame: " << ff->tamanho_frame << endl;
    cout << "n_param_entrada: " << ff->n_param_entrada << endl;
    cout << "n_maximo_param_saida: " << ff->n_maximo_param_saida << endl;
    cout << "n_pseudo_registradores: " << ff->n_pseudo_registradores << endl;
    cout << "n_variaveis_no_frame: " << ff->n_variaveis_no_frame << endl;
    ff->print_detalhes(func);
  }

  return 0;
}
