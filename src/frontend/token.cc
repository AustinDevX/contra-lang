//
// Created by austindevx on 1/7/17.
//
#include "token.h"

namespace frontend{

  const std::unordered_map<std::string, TokenType> Token::KEYWORDS = createKeywordsMap();
  const std::unordered_map<char*, TokenType> Token::SYMBOLS = createSymbolsMap();
}
