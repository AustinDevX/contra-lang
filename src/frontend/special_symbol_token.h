//
// Created by austindevx on 1/23/17.
//

#ifndef CONTRA_LANG_SPECIAL_SYMBOL_TOKEN_H
#define CONTRA_LANG_SPECIAL_SYMBOL_TOKEN_H

#include "token.h"

namespace frontend {
  class SpecialTokenSymbol : public Token {
    explicit SpecialTokenSymbol(Source* source);
    void extract() override;
  };
}


#endif //CONTRA_LANG_SPECIAL_SYMBOL_TOKEN_H
