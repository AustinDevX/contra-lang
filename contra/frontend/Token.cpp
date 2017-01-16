//
// Created by austindevx on 1/7/17.
//
#include "Token.h"

namespace frontend{

  const std::unordered_map<std::string, TokenType> Token::KEYWORDS = createKeywordsMap();
  const std::unordered_map<std::string, TokenType> Token::SYMBOLS = createSymbolsMap();
}
