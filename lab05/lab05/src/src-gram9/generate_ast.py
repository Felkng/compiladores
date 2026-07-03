import os

nodes = [
    ("ExpressaoMaior", "MAIOR (>)"),
    ("ExpressaoMaiorIgual", "MAIOR IGUAL (>=)"),
    ("ExpressaoMenorIgual", "MENOR IGUAL (<=)"),
    ("ExpressaoDiferente", "DIFERENTE (!=)"),
    ("ExpressaoAnd", "AND (&&)"),
    ("ExpressaoOr", "OR (||)"),
]

for name, desc in nodes:
    hpp = f"""#ifndef _{name.upper()}_HPP_
#define _{name.upper()}_HPP_

#include "Expressao.hpp"

class {name} : public Expressao {{
public:
  Expressao* esquerda;
  Expressao* direita;
  void debug_com_tab(int tab);
}};

#endif
"""
    cpp = f"""#include "{name}.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

void {name}::debug_com_tab(int tab) {{
  tab3(tab);
  cerr << "{desc}" << endl;
  esquerda->debug_com_tab(tab+1);
  direita->debug_com_tab(tab+1);
}}
"""
    with open(f"/home/felkng/Documents/faculdade/compiladores/lab03/lab03-atual/lab03-atual/src/src-gram9/{name}.hpp", "w") as f:
        f.write(hpp)
    with open(f"/home/felkng/Documents/faculdade/compiladores/lab03/lab03-atual/lab03-atual/src/src-gram9/{name}.cpp", "w") as f:
        f.write(cpp)

cast_hpp = """#ifndef _EXPRESSAOCAST_HPP_
#define _EXPRESSAOCAST_HPP_

#include "Expressao.hpp"
#include "Tipo.hpp"

class ExpressaoCast : public Expressao {
public:
  Expressao* expressao;
  Tipo* tipo;
  void debug_com_tab(int tab);
};

#endif
"""
cast_cpp = """#include "ExpressaoCast.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

void ExpressaoCast::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "CAST (" << tipo->nome() << ")" << endl;
  expressao->debug_com_tab(tab+1);
}
"""
with open(f"/home/felkng/Documents/faculdade/compiladores/lab03/lab03-atual/lab03-atual/src/src-gram9/ExpressaoCast.hpp", "w") as f:
    f.write(cast_hpp)
with open(f"/home/felkng/Documents/faculdade/compiladores/lab03/lab03-atual/lab03-atual/src/src-gram9/ExpressaoCast.cpp", "w") as f:
    f.write(cast_cpp)

call_hpp = """#ifndef _EXPRESSAOCHAMADA_HPP_
#define _EXPRESSAOCHAMADA_HPP_

#include "Expressao.hpp"
#include "ID.hpp"
#include <vector>

class ExpressaoChamada : public Expressao {
public:
  ID* nome;
  std::vector<Expressao*> argumentos;
  void debug_com_tab(int tab);
};

#endif
"""
call_cpp = """#include "ExpressaoChamada.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

void ExpressaoChamada::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "CALL " << nome->nome << "()" << endl;
  for (int i=0; i<argumentos.size(); ++i) {
    argumentos[i]->debug_com_tab(tab+1);
  }
}
"""
with open(f"/home/felkng/Documents/faculdade/compiladores/lab03/lab03-atual/lab03-atual/src/src-gram9/ExpressaoChamada.hpp", "w") as f:
    f.write(call_hpp)
with open(f"/home/felkng/Documents/faculdade/compiladores/lab03/lab03-atual/lab03-atual/src/src-gram9/ExpressaoChamada.cpp", "w") as f:
    f.write(call_cpp)

minus_hpp = """#ifndef _EXPRESSAOMENOSUNARIO_HPP_
#define _EXPRESSAOMENOSUNARIO_HPP_

#include "Expressao.hpp"

class ExpressaoMenosUnario : public Expressao {
public:
  Expressao* expressao;
  void debug_com_tab(int tab);
};

#endif
"""
minus_cpp = """#include "ExpressaoMenosUnario.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

void ExpressaoMenosUnario::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "UNARY MINUS (-)" << endl;
  expressao->debug_com_tab(tab+1);
}
"""
with open(f"/home/felkng/Documents/faculdade/compiladores/lab03/lab03-atual/lab03-atual/src/src-gram9/ExpressaoMenosUnario.hpp", "w") as f:
    f.write(minus_hpp)
with open(f"/home/felkng/Documents/faculdade/compiladores/lab03/lab03-atual/lab03-atual/src/src-gram9/ExpressaoMenosUnario.cpp", "w") as f:
    f.write(minus_cpp)
