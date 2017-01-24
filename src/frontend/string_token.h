//
// Created by austindevx on 1/21/17.
//

#ifndef CONTRA_LANG_STRINGTOKEN_H
#define CONTRA_LANG_STRINGTOKEN_H

#include "token.h"
#include "source.h"

namespace frontend {
  class StringToken : public Token {
  public:
    explicit StringToken(Source* source): Token{ source }{ extract(); };
    void extract() override;
  };
}


#endif //CONTRA_LANG_STRINGTOKEN_H
