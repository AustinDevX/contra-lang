//
// Created by austindevx on 1/23/17.
//

#include "special_symbol_token.h"
#include <string>

frontend::SpecialTokenSymbol::SpecialTokenSymbol(Source *source) : Token { source } { extract(); };

void frontend::SpecialTokenSymbol::extract() {
  char currentChar = getCurrentCharacter();
  std::string text(1, currentChar);

  switch(currentChar) {
    case '(': case ')': case '{': case'}': case '[': case ']': case'<': case'>': case '.': case ',': case '*':
    case '-': case '+': case '%': case ';': case ':': case '\"': case '~': case '^':
      getNextCharacter();
      break;
    case '/': case '=': case '&': case '|':
      if(currentChar == getNextCharacter()) {
        text.push_back(currentChar);
        getNextCharacter();
      }
      break;
    case '!':
      if(getNextCharacter() == '=') {
        text.push_back(getCurrentCharacter());
      }
      getNextCharacter();
      break;
  }
  this->text = text;

  type = SYMBOLS.at(this->text.c_str());
}
