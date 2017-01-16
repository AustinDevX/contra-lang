//
// Created by austindevx on 1/7/17.
//

#ifndef CONTRA_LANG_EOFTOKEN_H
#define CONTRA_LANG_EOFTOKEN_H

#include "Token.h"

namespace frontend {
  class EofToken : public Token {
  public:
    explicit EofToken(Source* source) : Token {source} {
      type = END_OF_FILE;
    };
  };
}


#endif //CONTRA_LANG_EOFTOKEN_H
