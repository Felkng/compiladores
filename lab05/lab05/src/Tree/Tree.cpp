#include <iostream>
#include "Exp.hpp"
#include "Stm.hpp"
#include "ExpBinop.hpp"
#include "ExpCall.hpp"
#include "ExpConst.hpp"
#include "ExpEseq.hpp"
#include "ExpMem.hpp"
#include "ExpName.hpp"
#include "ExpTemp.hpp"
#include "ExpTempFramePointer.hpp"
#include "StmCJump.hpp"
#include "StmExp.hpp"
#include "StmJump.hpp"
#include "StmLabel.hpp"
#include "StmMove.hpp"
#include "StmSeq.hpp"

#include "Operador.hpp"
#include "OperadorSoma.hpp"
#include "OperadorSubtracao.hpp"
#include "OperadorMultiplicacao.hpp"
#include "OperadorDivisao.hpp"
#include "OperadorMod.hpp"
#include "OperadorMenor.hpp"
#include "OperadorMaior.hpp"
#include "OperadorMenorIgual.hpp"
#include "OperadorMaiorIgual.hpp"
#include "OperadorIgualdade.hpp"
#include "OperadorDiferente.hpp"
#include "OperadorAnd.hpp"
#include "OperadorOr.hpp"

using namespace std;

// ExpBinop
ExpBinop::ExpBinop(Operador* o, Exp* e, Exp* d) : op(o), esq(e), dir(d) {}
ExpBinop::~ExpBinop() {
  delete op;
  delete esq;
  delete dir;
}
string ExpBinop::to_string() {
  string op_str = "";
  if (dynamic_cast<OperadorSoma*>(op)) op_str = "PLUS";
  else if (dynamic_cast<OperadorSubtracao*>(op)) op_str = "MINUS";
  else if (dynamic_cast<OperadorMultiplicacao*>(op)) op_str = "MUL";
  else if (dynamic_cast<OperadorDivisao*>(op)) op_str = "DIV";
  else if (dynamic_cast<OperadorMod*>(op)) op_str = "MOD";
  else if (dynamic_cast<OperadorMenor*>(op)) op_str = "LT";
  else if (dynamic_cast<OperadorMaior*>(op)) op_str = "GT";
  else if (dynamic_cast<OperadorMenorIgual*>(op)) op_str = "LE";
  else if (dynamic_cast<OperadorMaiorIgual*>(op)) op_str = "GE";
  else if (dynamic_cast<OperadorIgualdade*>(op)) op_str = "EQ";
  else if (dynamic_cast<OperadorDiferente*>(op)) op_str = "NE";
  else if (dynamic_cast<OperadorAnd*>(op)) op_str = "AND";
  else if (dynamic_cast<OperadorOr*>(op)) op_str = "OR";
  return "BINOP(" + op_str + ", " + esq->to_string() + ", " + dir->to_string() + ")";
}

// ExpCall
ExpCall::ExpCall(Exp* f, vector<Exp*> p) : nome_funcao(f), parametros(p) {}
ExpCall::~ExpCall() {
  delete nome_funcao;
  for (Exp* p : parametros) delete p;
}
string ExpCall::to_string() {
  string s = "CALL(" + nome_funcao->to_string();
  for (Exp* p : parametros) {
    s += ", " + p->to_string();
  }
  s += ")";
  return s;
}

// ExpConst
ExpConst::ExpConst(int v) : valor(v) {}
ExpConst::~ExpConst() {}
string ExpConst::to_string() {
  return "CONST " + std::to_string(valor);
}

// ExpEseq
ExpEseq::ExpEseq(Stm* s, Exp* e) : stm(s), exp(e) {}
ExpEseq::~ExpEseq() {
  delete stm;
  delete exp;
}
string ExpEseq::to_string() {
  return string("ESEQ(") + (stm ? "STM" : "null") + ", " + exp->to_string() + ")";
}

// ExpMem
ExpMem::ExpMem(Exp* e) : endereco(e) {}
ExpMem::~ExpMem() {
  delete endereco;
}
string ExpMem::to_string() {
  return "MEM(" + endereco->to_string() + ")";
}

// ExpName
ExpName::ExpName(string n) : nome(n) {}
ExpName::~ExpName() {}
string ExpName::to_string() {
  return "NAME " + nome;
}

// ExpTemp
ExpTemp::ExpTemp(int i) : id(i) {}
ExpTemp::~ExpTemp() {}
string ExpTemp::to_string() {
  return "TEMP " + std::to_string(id);
}

// ExpTempFramePointer
ExpTempFramePointer::ExpTempFramePointer() : ExpTemp(-1) {}
ExpTempFramePointer::~ExpTempFramePointer() {}
string ExpTempFramePointer::to_string() {
  return "FP";
}

// StmCJump
StmCJump::StmCJump(Exp* cond, string t, string f) : expressao_booleana(cond), destino_verdade(t), destino_falso(f) {}
StmCJump::~StmCJump() {
  delete expressao_booleana;
}
void StmCJump::print() {
  cout << "CJUMP(" << expressao_booleana->to_string() << ", " << destino_verdade << ", " << destino_falso << ")" << endl;
}

// StmExp
StmExp::StmExp(Exp* e) : exp(e) {}
StmExp::~StmExp() {
  delete exp;
}
void StmExp::print() {
  cout << "EXP(" << exp->to_string() << ")" << endl;
}

// StmJump
StmJump::StmJump(Exp* dest, vector<string> targets) : destino(dest), alvos(targets) {}
StmJump::~StmJump() {
  delete destino;
}
void StmJump::print() {
  cout << "JUMP(" << destino->to_string() << ")" << endl;
}

// StmLabel
StmLabel::StmLabel(string n) : nome(n) {}
StmLabel::~StmLabel() {}
void StmLabel::print() {
  cout << "LABEL " << nome << endl;
}

// StmMove
StmMove::StmMove(Exp* dest, Exp* src) : destino(dest), origem(src) {}
StmMove::~StmMove() {
  delete destino;
  delete origem;
}
void StmMove::print() {
  cout << "MOVE(" << destino->to_string() << ", " << origem->to_string() << ")" << endl;
}

// StmSeq
StmSeq::StmSeq(Stm* l, Stm* r) : esq(l), dir(r) {}
StmSeq::~StmSeq() {
  delete esq;
  delete dir;
}
void StmSeq::print() {
  if (esq) esq->print();
  if (dir) dir->print();
}
