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
#include "Analisador.hpp"


int main(int argc, char * argv[]) {
  if (argc < 3) {
    cerr << "Uso: compilador <gramatica> <tabela_lr1> [parametros.params]" << endl;
    return 1;
  }
  string nome_gramatica = argv[1];
  string nome_tab_lr1 = argv[2];
  string nome_params = (argc > 3) ? argv[3] : "";

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
  cerr << "Funcao extraida. Lendo parametros..." << endl;
  vector<ValorLiteral> parametros_passados;
  if (!nome_params.empty()) {
    ifstream arq_params(nome_params);
    string linha;
    while (getline(arq_params, linha)) {
      if (linha.empty()) continue;
      stringstream ss(linha);
      string tipo, val;
      ss >> tipo >> val;
      ValorLiteral vl;
      if (tipo == "INT" || tipo == "i32") {
        vl.tipo = new Tipo(Tipo::INT);
        vl.valor_int = stoi(val);
      } else if (tipo == "FLOAT" || tipo == "f32") {
        vl.tipo = new Tipo(Tipo::FLOAT);
        vl.valor_float = stof(val);
      } else if (tipo == "BOOL" || tipo == "bool") {
        vl.tipo = new Tipo(Tipo::BOOL);
        vl.valor_bool = (val == "true" || val == "1");
      }
      parametros_passados.push_back(vl);
    }
  }
  cerr << "Parametros lidos. Calculando retorno..." << endl;

  Analisador ana;
  ana.calcula_retorno(func, parametros_passados);
  return 0;
}
