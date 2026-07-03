#ifndef _FRAME_FUNCAO_HPP_
#define _FRAME_FUNCAO_HPP_
#include "../src-gram9/Funcao.hpp"
#include <map>

class FrameAcesso;

using namespace std;

class FrameFuncao {
public:
  int tamanho_frame;
  int n_param_entrada;
  int n_maximo_param_saida;
  int n_pseudo_registradores;
  int n_variaveis_no_frame;
  std::map<Variavel*, FrameAcesso*> acessos;

  FrameFuncao();
  static FrameFuncao* gera_frame_de_funcao(Funcao* fun);
  void print_detalhes(Funcao* fun);
};

#endif
