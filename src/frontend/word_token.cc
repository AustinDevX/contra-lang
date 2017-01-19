//
// Created by austindevx on 1/16/17.
//
#include "word_token.h"

using namespace frontend;

WordToken::WordToken(frontend::Source *source) : Token(source){
  extract();
};

void WordToken::extract() {
  std::string text;
  char current = getCurrentCharacter();
  // starting at the current character consume characters in the source until a non valid character is found.
  while(isValidWordCharacter(current)) {
    text.push_back(current);
    current = getNextCharacter();
  }
  this->text = text;
  try {
    type = KEYWORDS.at(text);
  } catch (std::out_of_range) {
    type = IDENTIFIER;
  }
}

bool WordToken::isValidWordCharacter(char c) {
  return (isalnum(c) || c == '_');
}

