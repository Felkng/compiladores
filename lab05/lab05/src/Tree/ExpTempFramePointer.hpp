#ifndef _EXP_TEMPFRAMEPOINTER_HPP_
#define _EXP_TEMPFRAMEPOINTER_HPP_
#include "Exp.hpp"
#include "ExpTemp.hpp"
#include "../src-gram9/Expressao.hpp"

class ExpTempFramePointer : public ExpTemp {
public:
  ExpTempFramePointer();
  virtual ~ExpTempFramePointer();
  virtual string to_string() override;
};

#endif
